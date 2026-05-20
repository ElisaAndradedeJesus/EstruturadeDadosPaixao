#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "team.h"
#include "partida.h"
#include "bdteams.h"
#include "bdpartidas.h"

struct bdpartidas{
    int nElementos; //número de elementos atualmente na lista
    int capacidade; //capacidade máxima da lista
    Partida** partidas; //array de ponteiros para as partidas
};

// Função para criar um banco de dados de partidas
BDPartidas *criarBDPartidas() {
    BDPartidas* bd = (BDPartidas*)malloc(sizeof(BDPartidas));
    if (bd == NULL) {
        printf("Erro ao alocar memória para o banco de dados de partidas.\n");
        return NULL;
    }
    bd->nElementos = 0;
    bd->capacidade = 10; // Capacidade inicial, pode ser ajustada conforme necessário
    bd->partidas = (Partida**)malloc(bd->capacidade * sizeof(Partida*));
    if (bd->partidas == NULL) {
        printf("Erro ao alocar memória para as partidas no banco de dados.\n");
        free(bd);
        return NULL;
    }
    return bd;
}

//Função para almentar a capacidade do banco de dados de partidas
static int reallocateBDPartidas(BDPartidas* bd) {
    Partida** temp = (Partida**)realloc(bd->partidas, bd->capacidade * 2 * sizeof(Partida*));   
    // Verifica se a realocação foi bem-sucedida
    if (temp == NULL) {
        printf("Erro ao realocar memória para as partidas no banco de dados.\n");
        return 0;
    }
    bd->partidas = temp;
    bd->capacidade *= 2;
    return 1;
}
// insere uma partida no banco de dados
int adicionarPartida(BDPartidas* bd, Partida* partida) {
    if (bd->nElementos == bd->capacidade) {
        if (reallocateBDPartidas(bd) == 0) {
            printf("Erro ao realocar memória para as partidas no banco de dados.\n");
            return 0;
        }
    }
    bd->partidas[bd->nElementos++] = partida;
    return 1;
}

//cria Vetor de um arquivo externo
BDPartidas* criarBDPartidasDeArquivo(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return NULL;
    }

    BDPartidas* bd = criarBDPartidas();  // Cria um banco de dados com capacidade inicial
    if (bd == NULL) {
        fclose(arquivo);
        return NULL;
    }

    // pula cabeçalho do arquivo
    char linha[100];
    fgets(linha, sizeof(linha), arquivo);

    // CHECAR DE ESSE WHILE ESTÁ CERTO, SE O FEOF FUNCIONA PARA O FORMATO DO ARQUIVO
    int id, time1, time2, golsTime1, golsTime2;

    // Lê as partidas do arquivo e as adiciona ao banco de dados
    while (fscanf(arquivo, " %d,%d,%d,%d,%d", &id, &time1, &time2, &golsTime1, &golsTime2) == 5) {
        Partida* partida = criarPartida(id, time1, time2, golsTime1, golsTime2);
        if (partida == NULL) {
            printf("Erro ao criar partida a partir dos dados do arquivo.\n");
            break;
        }
        int adicionado = adicionarPartida(bd, partida);
        if (adicionado == 0) {
            free(partida);
            printf("Erro ao adicionar partida ao banco de dados.\n");
            break;
        }
    }

    fclose(arquivo);
    return bd;
}

int getSizeofBDPartidas(BDPartidas* bd) {
    if (bd != NULL) {
        return bd->nElementos;
    }
    return -1;  // Valor inválido se o banco de dados for NULL
}

Partida* getPartida(BDPartidas* bd, int index) {
    if (bd != NULL && index >= 0 && index < bd->nElementos) {
        return bd->partidas[index];
    }
    return NULL;  // Retorna NULL se o índice for inválido ou o banco de dados for NULL
}

// Função para buscar partidas onde o time mandante tem um nome que corresponde ao prefixo fornecido
BDPartidas* buscarPartidaPorNomeTimeMandante(BDPartidas* bdPartidas, char* prefixo, BDTeams* bdTeams) {
    BDPartidas* partidasEncontradas = criarBDPartidas(); // Cria um novo banco de dados para armazenar as partidas encontradas
    BDTeams* timesComPrefixo = buscarPorTeamNoBD(bdTeams, prefixo); // Busca os times que correspondem ao prefixo fornecido

    for (int i = 0; i < getSizeofBDPartidas(bdPartidas); i++) {
        Partida* p = getPartida(bdPartidas, i);
        for (int j = 0; j < getSizeofBDTeams(timesComPrefixo); j++) {
            Team* t = getTeam(timesComPrefixo, j);
            if (getIdTime1(p) == getIdTeam(t)) { // Verifica se o time é o mandante
                int sucesso = adicionarPartida(partidasEncontradas, p); // Adiciona a partida ao banco de dados de partidas encontradas
                if (sucesso == 0) {
                    liberarBDPartidasAux(partidasEncontradas);
                    return NULL; // Retorna NULL em caso de erro ao adicionar a partida
                }
            }
        }
    }

    liberarBDTeamsAux(timesComPrefixo);
    return partidasEncontradas; // Retorna o banco de dados com as partidas encontradas
}

// Função para buscar partidas onde o time visitante tem um nome que corresponde ao prefixo fornecido
BDPartidas* buscarPartidaPorNomeTimeVisitante(BDPartidas* bdPartidas, char* prefixo, BDTeams* bdTeams) {
    BDPartidas* partidasEncontradas = criarBDPartidas(); // Cria um novo banco de dados para armazenar as partidas encontradas
    BDTeams* timesComPrefixo = buscarPorTeamNoBD(bdTeams, prefixo); // Busca os times que correspondem ao prefixo fornecido

    for (int i = 0; i < getSizeofBDPartidas(bdPartidas); i++) {
        Partida* p = getPartida(bdPartidas, i);
        for (int j = 0; j < getSizeofBDTeams(timesComPrefixo); j++) {
            Team* t = getTeam(timesComPrefixo, j);
            if (getIdTime2(p) == getIdTeam(t)) { // Verifica se o time é o mandante
                int sucesso = adicionarPartida(partidasEncontradas, p); // Adiciona a partida ao banco de dados de partidas encontradas
                if (sucesso == 0) {
                    liberarBDPartidasAux(partidasEncontradas);
                    return NULL; // Retorna NULL em caso de erro ao adicionar a partida
                }
            }
        }
    }

    liberarBDTeamsAux(timesComPrefixo);
    return partidasEncontradas; // Retorna o banco de dados com as partidas encontradas
}

// Função para liberar memória alocada para o banco de dados de partidas
void liberarBDPartidas(BDPartidas* bd) {
    if (bd != NULL) {
        for (int i = 0; i < bd->nElementos; i++) {
            liberarPartida(bd->partidas[i]);            
        }
        free(bd->partidas);
        free(bd);
    }
}

// Função para liberar memória alocada para o banco de dados de partidas, sem liberar as partidas individuais 
// (útil para casos onde as partidas são compartilhadas entre diferentes bancos de dados)
void liberarBDPartidasAux(BDPartidas* bd) {
    if (bd != NULL) {
        free(bd->partidas);
        free(bd);
    }
}