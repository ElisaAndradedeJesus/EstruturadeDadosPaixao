#ifndef PARTIDA_H
#define PARTIDA_H

#include <assert.h>

typedef struct partida Partida;

Partida* criarPartida(int id, int idTeam1, int idTeam2, int golsTeam1, int golsTeam2);

// ===================================================================
// FUNÇÕES GET PARA ACESSAR OS ATRIBUTOS DA PARTIDA

// Função para acessar Id da partida
int getIdPartida(Partida* p);

/// Função para acessar Id do team 1
int getIdTeam1(Partida* p);

/// Função para acessar Id do team 2
int getIdTeam2(Partida* p);

/// Função para acessar gols do team 1
int getGolsTeam1(Partida* p);

/// Função para acessar gols do team 2
int getGolsTeam2(Partida* p);

// ===================================================================

// Função para alterar/definir o placar da partida
void setPlacarPartida(Partida* p, int golsTeam1, int golsTeam2);

// ===================================================================

/// Função para liberar memória alocada para a partida
void liberarPartida(Partida* p);

#endif // PARTIDA_H