#ifndef PARTIDA_H
#define PARTIDA_H

#include <assert.h>

typedef struct partida Partida;

Partida* criarPartida(int id, int idTime1, int idTime2, int golsTime1, int golsTime2);

// ===================================================================
// FUNÇÕES GET PARA ACESSAR OS ATRIBUTOS DA PARTIDA

// Função para acessar Id da partida
int getIdPartida(Partida* p);

/// Função para acessar Id do time 1
int getIdTime1(Partida* p);

/// Função para acessar Id do time 2
int getIdTime2(Partida* p);

/// Função para acessar gols do time 1
int getGolsTime1(Partida* p);

/// Função para acessar gols do time 2
int getGolsTime2(Partida* p);

// ===================================================================

/// Função para liberar memória alocada para a partida
void liberarPartida(Partida* p);

#endif // PARTIDA_H