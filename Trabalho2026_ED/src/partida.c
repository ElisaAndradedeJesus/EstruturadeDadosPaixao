#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "partida.h"

struct partida {
    int id;
    int idTime1;
    int idTime2;
    int golsTime1;
    int golsTime2;
};

Partida* criarPartida(int id, int idTime1, int idTime2, int golsTime1, int golsTime2) {
    Partida* p = (Partida*)malloc(sizeof(Partida));
    if (p == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a partida.\n");
        exit(EXIT_FAILURE);
    }
    p->id = id;
    p->idTime1 = idTime1;
    p->idTime2 = idTime2;
    p->golsTime1 = golsTime1;
    p->golsTime2 = golsTime2;
    return p;
}

// Função para acessar Id da partida
int getIdPartida(Partida* p) {
    assert(p != NULL);
    return p->id;
}


/// Função para acessar Id do time 1
int getIdTime1(Partida* p) {
    assert(p != NULL);
    return p->idTime1;
}

// Função para acessar Id do time 2
int getIdTime2(Partida* p) {
    assert(p != NULL);
    return p->idTime2;
}

// Função para acessar gols do time 1
int getGolsTime1(Partida* p) {
    assert(p != NULL);
    return p->golsTime1;
}

// Função para acessar gols do time 2
int getGolsTime2(Partida* p) {
    assert(p != NULL);
    return p->golsTime2;
}




// Função para liberar memória alocada para a partida
void liberarPartida(Partida* p) {
    if (p != NULL) {
        free(p);
    }
}
