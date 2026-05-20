#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "team.h"
#include "partida.h"
#include "bdteams.h"
#include "bdpartidas.h"

struct bdteams{
    int nElementos; //número de elementos atualmente na lista
    int capacidade; //capacidade máxima da lista
    Team** teams; //array de ponteiros para os teams
};

BDTeams* criarBDTeams() {
    BDTeams* bd = (BDTeams*)malloc(sizeof(BDTeams));
    if (bd == NULL) {
        printf("Erro ao alocar memória para o banco de dados de times.\n");
        return NULL;
    }
    bd->nElementos = 0;
    bd->capacidade = 10; // Capacidade inicial, pode ser ajustada conforme necessário
    bd->teams = (Team**)malloc(bd->capacidade * sizeof(Team*));
    if (bd->teams == NULL) {
        fprintf(stderr, "Erro ao alocar memória para os times no banco de dados.\n");
        free(bd);
        return NULL;
    }
    return bd;
}

//Função para almentar a capacidade do banco de dados de times
static int reallocateBDTeams(BDTeams* bd) {
    Team** temp = (Team**)realloc(bd->teams, bd->capacidade * 2 * sizeof(Team*));

    // Verifica se a realocação foi bem-sucedida
    if (temp == NULL) {
        printf("Erro ao realocar memória para os times no banco de dados.\n");
        return 0;
    }
    bd->teams = temp;
    bd->capacidade *= 2;
    return 1;
}

//cria Vetor de um arquivo externo
BDTeams* criarBDTeamsDeArquivo(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return NULL;
    }

    BDTeams* bd = criarBDTeams();  // Cria um banco de dados com capacidade inicial
    if (bd == NULL) {
        fclose(arquivo);
        return NULL;
    }

    // pula cabeçalho do arquivo
    char linha[100];
    fgets(linha, sizeof(linha), arquivo);

    // Lê os dados do arquivo e adiciona os times ao banco de dados
    int id;
    char nomeTime[50];
    while (fscanf(arquivo, " %d,%49[^\n]", &id, nomeTime) == 2) {
        Team* t = criarTeam(id, nomeTime);
        if (t == NULL) {
            liberarBDTeams(bd);
            fclose(arquivo);
            return NULL;
        }
        if(bd->nElementos < bd->capacidade){
            // Adiciona o time ao banco de dados
            bd->teams[bd->nElementos++] = t;

        }else{
            int sucesso = reallocateBDTeams(bd);
            if(sucesso == 1){
                // Adiciona o time ao banco de dados
                bd->teams[bd->nElementos++] = t;
            }else{
                liberarBDTeams(bd);
                fclose(arquivo);
                return NULL;
            }
        }
        

    }

    fclose(arquivo);
    return bd;
}

// Função para aber o tamanho do banco de dados de times
int getSizeofBDTeams(BDTeams* bd) {
    assert(bd != NULL);
    return bd->nElementos;
}

// Função para acessar um time específico do banco de dados
Team* getTeam(BDTeams* bd, int index) {
    assert(bd != NULL);
    assert(index >= 0 && index < bd->nElementos);
    return bd->teams[index];
}

// Função para adicionar um time ao banco de dados de times
void adicionarTeam(BDTeams* bd, Team* t) {
    if (bd == NULL || t == NULL) {
        printf("Erro: Banco de dados ou time é NULL. Não é possível adicionar o time.\n");
        return;
    }
    if (bd->nElementos >= bd->capacidade) {
        int sucesso = reallocateBDTeams(bd);
        if (!sucesso) {
            printf("Erro ao realocar memória para os times no banco de dados. Time não adicionado.\n");
            return;
        }
    }
    bd->teams[bd->nElementos++] = t;
}

// Função para buscar um time pelo ID no banco de dados de times
// É uma função auxiliar para facilitar a atualização dos dados dos times com base nas partidas
Team* buscarTeamPorId(BDTeams* bd, int id) {
    for (int i = 0; i < getSizeofBDTeams(bd); i++) {
        Team* t = getTeam(bd, i);
        if (getIdTeam(t) == id) {
            return t;
        }
    }
    return NULL; // Retorna NULL se o time não for encontrado
}

//Pega os Dados de uma partida e atualiza os dados dos times envolvidos na partida, como vitórias, empates, derrotas, gols marcados e gols sofridos
// Função auxiliar de carregarDadosDePartidasEmTimes, que é a função principal para carregar os dados de todas as partidas e atualizar os dados dos times no banco de dados de times
void carregarDadosEmTimes(BDTeams* bd, Partida* p) {
    // Atualiza a tabela de classificação com base no resultado da partida
    int idTime1 = getIdTime1(p);
    int idTime2 = getIdTime2(p);
    int golsTime1 = getGolsTime1(p);
    int golsTime2 = getGolsTime2(p);

    Team* time1 = buscarTeamPorId(bd, idTime1);
    Team* time2 = buscarTeamPorId(bd, idTime2);

    if (golsTime1 > golsTime2) {
        incrementarVitorias(time1);
        incrementarDerrotas(time2);
    } else if (golsTime1 < golsTime2) {
        incrementarDerrotas(time1);
        incrementarVitorias(time2);
    } else {
        incrementarEmpates(time1);
        incrementarEmpates(time2);
    }

    incrementarGolsMarcados(time1, golsTime1);
    incrementarGolsSofridos(time1, golsTime2);
    incrementarGolsMarcados(time2, golsTime2);
    incrementarGolsSofridos(time2, golsTime1);

}

// Função para buscar times pelo nome ou prefixo no banco de dados de times
BDTeams* buscarPorTeamNoBD(BDTeams* bd, char* prefixo) {
    BDTeams* resultados = criarBDTeams(); // Cria um novo banco de dados para armazenar os resultados
    for (int i = 0; i < getSizeofBDTeams(bd); i++) {
        Team* t = getTeam(bd, i);
        if (strncmp(getNome(t), prefixo, strlen(prefixo)) == 0) { // Verifica se o nome do time contém o prefixo fornecido
            adicionarTeam(resultados, t); // Adiciona o time ao banco de dados de resultados
        }
    }
    return resultados;
}

// Função para liberar memória alocada para o banco de dados de times
void liberarBDTeams(BDTeams* bd) {
    if (bd != NULL) {
        for (int i = 0; i < bd->nElementos; i++) {
            liberarTeam(bd->teams[i]);
        }
        free(bd->teams);
        free(bd);
    }
}


// Função para liberar memória alocada para o banco de dados de times, sem liberar os times individuais
// (útil para casos onde os times são compartilhados entre diferentes bancos de dados)
void liberarBDTeamsAux(BDTeams* bd) {
    if (bd != NULL) {
        free(bd->teams);
        free(bd);
    }
}