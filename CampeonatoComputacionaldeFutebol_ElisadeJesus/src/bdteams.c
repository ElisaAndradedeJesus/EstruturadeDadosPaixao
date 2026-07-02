#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <strings.h>

#include "team.h"
#include "partida.h"
#include "bdteams.h"
#include "bdpartidas.h"


struct bdteams{
    int nElementos; //número de elementos atualmente na lista
    struct TeamNode* primeiro;
    struct TeamNode* ultimo;
};

typedef struct TeamNode {
    Team* team;
    struct TeamNode* proximo;
} TeamNode;

BDTeams* criarBDTeams() {
    BDTeams* bd = (BDTeams*)malloc(sizeof(BDTeams));
    if (bd == NULL) {
        printf("Erro ao alocar memória para o banco de dados de teams.\n");
        return NULL;
    }
    bd->nElementos = 0;
    bd->primeiro = NULL;
    bd->ultimo = NULL;
    return bd;
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

    // Lê os dados do arquivo e adiciona os teams ao banco de dados
    int id;
    char nomeTeam[50];
    while (fscanf(arquivo, " %d,%49[^\n]", &id, nomeTeam) == 2) {
        Team* t = criarTeam(id, nomeTeam);
        if (t == NULL) {
            liberarBDTeams(bd);
            fclose(arquivo);
            return NULL;
        }
        adicionarTeam(bd, t);        

    }

    fclose(arquivo);
    return bd;
}

// Função para carregar os dados de todas as partidas e atualizar os dados dos teams no banco de dados de teams 
// só pode ser executada 1 vez a n ser que eu crie alguma forma de resertar os dados dos teams.
void carregarDadosDePartidasEmTeams(BDTeams* bdTeams, BDPartidas* bdPartidas) {
    for (int i = 0; i < getSizeofBDPartidas(bdPartidas); i++) {
        Partida* p = getPartida(bdPartidas, i);
        carregarDadosEmTeams(bdTeams, p);
    }
}

// Função para aber o tamanho do banco de dados de teams
int getSizeofBDTeams(BDTeams* bd) {
    assert(bd != NULL);
    return bd->nElementos;
}

// Função para acessar um team específico do banco de dados
Team* getTeam(BDTeams* bd, int index) {
    assert(bd != NULL);
    assert(index >= 0 && index < bd->nElementos);

    TeamNode* atual = bd->primeiro;

    for (int i = 0; i < index; i++) {
        atual = atual->proximo;
    }

    return atual->team;
}



// Função para adicionar um team ao banco de dados de teams
void adicionarTeam(BDTeams* bd, Team* t) {
    if (bd == NULL || t == NULL) {
        printf("Erro: Banco de dados ou team é NULL. Não é possível adicionar o team.\n");
        return;
    }
    TeamNode* novoNo = (TeamNode*)malloc(sizeof(TeamNode));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória para o novo nó da lista encadeada.\n");
        return;
    }
    novoNo->team = t;
    novoNo->proximo = NULL;

    if (bd->primeiro == NULL) {
        // Se a lista estiver vazia, o novo nó é o primeiro
        bd->primeiro = novoNo;
        bd->ultimo = novoNo;
    } else {
        // Caso contrário, adiciona o novo nó ao final da lista
        bd->ultimo->proximo = novoNo;
        bd->ultimo = novoNo;
    }
    bd->nElementos++;
}

// Função para buscar um team pelo ID no banco de dados de teams
// É uma função auxiliar para facilitar a atualização dos dados dos teams com base nas partidas
Team* buscarTeamPorId(BDTeams* bd, int id) {
    for (int i = 0; i < getSizeofBDTeams(bd); i++) {
        Team* t = getTeam(bd, i);
        if (getIdTeam(t) == id) {
            return t;
        }
    }
    return NULL; // Retorna NULL se o team não for encontrado
}

//Pega os Dados de uma partida e atualiza os dados dos teams envolvidos na partida, como vitórias, empates, derrotas, gols marcados e gols sofridos
// Função auxiliar de carregarDadosDePartidasEmTeams, que é a função principal para carregar os dados de todas as partidas e atualizar os dados dos teams no banco de dados de teams
void carregarDadosEmTeams(BDTeams* bd, Partida* p) {
    // Atualiza a tabela de classificação com base no resultado da partida
    int idTeam1 = getIdTeam1(p);
    int idTeam2 = getIdTeam2(p);
    int golsTeam1 = getGolsTeam1(p);
    int golsTeam2 = getGolsTeam2(p);

    Team* team1 = buscarTeamPorId(bd, idTeam1);
    Team* team2 = buscarTeamPorId(bd, idTeam2);

    if (golsTeam1 > golsTeam2) {
        incrementarVitorias(team1);
        incrementarDerrotas(team2);
    } else if (golsTeam1 < golsTeam2) {
        incrementarDerrotas(team1);
        incrementarVitorias(team2);
    } else {
        incrementarEmpates(team1);
        incrementarEmpates(team2);
    }

    incrementarGolsMarcados(team1, golsTeam1);
    incrementarGolsSofridos(team1, golsTeam2);
    incrementarGolsMarcados(team2, golsTeam2);
    incrementarGolsSofridos(team2, golsTeam1);

}

// Função para buscar teams pelo nome ou prefixo no banco de dados de teams
BDTeams* buscarPorTeamNoBD(BDTeams* bd, char* prefixo) {
    BDTeams* resultados = criarBDTeams(); // Cria um novo banco de dados para armazenar os resultados
    for (int i = 0; i < getSizeofBDTeams(bd); i++) {
        Team* t = getTeam(bd, i);
        if (strncasecmp(getNome(t), prefixo, strlen(prefixo)) == 0) { // Verifica se o nome do team contém o prefixo fornecido
            adicionarTeam(resultados, t); // Adiciona o team ao banco de dados de resultados
        }
    }
    return resultados;
}

//Função para limpar estatísticas de todos os teams
void limparEstatisticasBDTeams(BDTeams* bd) {
    if (bd != NULL) {
        for (int i = 0; i < getSizeofBDTeams(bd); i++) {
            Team* t = getTeam(bd, i);
            resetarEstatisticasTeam(t);
        }
    }
}

// Recalcula as estatísticas dos teams a partir da lista atual de partidas.
// Primeiro zera os dados acumulados para evitar contagem duplicada quando
// uma partida é inserida, removida ou atualizada.
void atualizarDadosTeam(BDTeams* bdTeams, BDPartidas* bdPartidas) {
    if (bdTeams == NULL || bdPartidas == NULL) {
        printf("Erro: Banco de dados de teams ou partidas é NULL.\n");
        return;
    }
    //resetar dados do banco de dados para garantir que não haja dados repetidos
    limparEstatisticasBDTeams(bdTeams);

    for (int i = 0; i < getSizeofBDPartidas(bdPartidas); i++) {
        Partida* p = getPartida(bdPartidas, i);
        carregarDadosEmTeams(bdTeams, p);
    }
}



// Função para liberar memória alocada para o banco de dados de teams
void liberarBDTeams(BDTeams* bd) {
    if (bd != NULL) {
        TeamNode* atual = bd->primeiro;

        while (atual != NULL) {
            TeamNode* proximo = atual->proximo;
            liberarTeam(atual->team);
            free(atual);
            atual = proximo;
        }

        free(bd);
    }
}


// Função para liberar memória alocada para o banco de dados de teams, sem liberar os teams individuais
// (útil para casos onde os teams são compartilhados entre diferentes bancos de dados)
void liberarBDTeamsAux(BDTeams* bd) {
    if (bd != NULL) {
        TeamNode* atual = bd->primeiro;

        while (atual != NULL) {
            TeamNode* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }

        free(bd);
    }
}