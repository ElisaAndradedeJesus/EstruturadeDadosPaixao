#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "partida.h"

struct partida {
    int id;
    int idTeam1;
    int idTeam2;
    int golsTeam1;
    int golsTeam2;
};

Partida* criarPartida(int id, int idTeam1, int idTeam2, int golsTeam1, int golsTeam2) {
    Partida* p = (Partida*)malloc(sizeof(Partida));
    if (p == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a partida.\n");
        exit(EXIT_FAILURE);
    }
    p->id = id;
    p->idTeam1 = idTeam1;
    p->idTeam2 = idTeam2;
    p->golsTeam1 = golsTeam1;
    p->golsTeam2 = golsTeam2;
    return p;
}

// ===================================================================
// FUNÇÕES GET PARA ACESSAR OS ATRIBUTOS DA PARTIDA

// Função para acessar Id da partida
int getIdPartida(Partida* p) {
    assert(p != NULL);
    return p->id;
}


/// Função para acessar Id do team 1
int getIdTeam1(Partida* p) {
    assert(p != NULL);
    return p->idTeam1;
}

// Função para acessar Id do team 2
int getIdTeam2(Partida* p) {
    assert(p != NULL);
    return p->idTeam2;
}

// Função para acessar gols do team 1
int getGolsTeam1(Partida* p) {
    assert(p != NULL);
    return p->golsTeam1;
}

// Função para acessar gols do team 2
int getGolsTeam2(Partida* p) {
    assert(p != NULL);
    return p->golsTeam2;
}

// ===================================================================

// Função para alterar/definir o placar da partida
void setPlacarPartida(Partida* p, int golsTeam1, int golsTeam2) {
    if (p != NULL) {
        p->golsTeam1 = golsTeam1;
        p->golsTeam2 = golsTeam2;
    }
}

// ===================================================================

// Função para liberar memória alocada para a partida
void liberarPartida(Partida* p) {
    if (p != NULL) {
        free(p);
    }
}

