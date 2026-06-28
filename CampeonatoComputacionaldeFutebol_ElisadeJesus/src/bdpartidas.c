#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "team.h"
#include "partida.h"
#include "bdteams.h"
#include "bdpartidas.h"

typedef struct PartidaNode {
    Partida* partida;
    struct PartidaNode* proximo;
} PartidaNode;

struct bdpartidas {
    int nElementos;
    PartidaNode* primeiro;
    PartidaNode* ultimo;
};

// Função para criar um banco de dados de partidas
BDPartidas *criarBDPartidas() {
    BDPartidas* bd = (BDPartidas*)malloc(sizeof(BDPartidas));
    if (bd == NULL) {
        printf("Erro ao alocar memória para o banco de dados de partidas.\n");
        return NULL;
    }
    bd->nElementos = 0;
    bd->primeiro = NULL;
    bd->ultimo = NULL;

    return bd;
}


// insere uma partida no banco de dados
int adicionarPartida(BDPartidas* bd, Partida* partida) {
    PartidaNode* novoNo = (PartidaNode*)malloc(sizeof(PartidaNode));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória para o novo nó da lista de partidas.\n");
        return 0;
    }
    novoNo->partida = partida;
    novoNo->proximo = NULL;

    if (bd->primeiro == NULL) {
        bd->primeiro = novoNo;
    } else {
        bd->ultimo->proximo = novoNo;
    }
    bd->ultimo = novoNo;
    bd->nElementos++;
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

    int id, team1, team2, golsTeam1, golsTeam2;

    // Lê as partidas do arquivo e as adiciona ao banco de dados
    while (fscanf(arquivo, " %d,%d,%d,%d,%d", &id, &team1, &team2, &golsTeam1, &golsTeam2) == 5) {
        Partida* partida = criarPartida(id, team1, team2, golsTeam1, golsTeam2);
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
        PartidaNode* atual = bd->primeiro;
        for (int i = 0; i < index; i++) {
            atual = atual->proximo;
        }
        return atual->partida;
    }
    return NULL;  // Retorna NULL se o índice for inválido ou o banco de dados for NULL
}

// Função para buscar partidas onde o team mandante tem um nome que corresponde ao prefixo fornecido
BDPartidas* buscarPartidaPorNomeTeamMandante(BDPartidas* bdPartidas, char* prefixo, BDTeams* bdTeams) {
    BDPartidas* partidasEncontradas = criarBDPartidas(); // Cria um novo banco de dados para armazenar as partidas encontradas
    BDTeams* timesComPrefixo = buscarPorTeamNoBD(bdTeams, prefixo); // Busca os times que correspondem ao prefixo fornecido

    for (int i = 0; i < getSizeofBDPartidas(bdPartidas); i++) {
        Partida* p = getPartida(bdPartidas, i);
        for (int j = 0; j < getSizeofBDTeams(timesComPrefixo); j++) {
            Team* t = getTeam(timesComPrefixo, j);
            if (getIdTeam1(p) == getIdTeam(t)) { // Verifica se o time é o mandante
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
BDPartidas* buscarPartidaPorNomeTeamVisitante(BDPartidas* bdPartidas, char* prefixo, BDTeams* bdTeams) {
    BDPartidas* partidasEncontradas = criarBDPartidas(); // Cria um novo banco de dados para armazenar as partidas encontradas
    BDTeams* timesComPrefixo = buscarPorTeamNoBD(bdTeams, prefixo); // Busca os times que correspondem ao prefixo fornecido

    for (int i = 0; i < getSizeofBDPartidas(bdPartidas); i++) {
        Partida* p = getPartida(bdPartidas, i);
        for (int j = 0; j < getSizeofBDTeams(timesComPrefixo); j++) {
            Team* t = getTeam(timesComPrefixo, j);
            if (getIdTeam2(p) == getIdTeam(t)) { // Verifica se o time é o mandante
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
        PartidaNode* atual = bd->primeiro;

        while (atual != NULL) {
            PartidaNode* proximo = atual->proximo;
            liberarPartida(atual->partida);
            free(atual);
            atual = proximo;
        }

        free(bd);
    }
}


// Função para liberar memória alocada para o banco de dados de partidas, sem liberar as partidas individuais 
// (útil para casos onde as partidas são compartilhadas entre diferentes bancos de dados)
void liberarBDPartidasAux(BDPartidas* bd) {
    if (bd != NULL) {
        PartidaNode* atual = bd->primeiro;

        while (atual != NULL) {
            PartidaNode* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }

        free(bd);
    }
}

