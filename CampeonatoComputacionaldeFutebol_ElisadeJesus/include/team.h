#ifndef TEAM_H
#define TEAM_H

#include <assert.h>

typedef struct team Team;

Team* criarTeam(int id, const char* nome);

// ===================================================================

// Função para acessar Id do team
int getIdTeam(Team* t);

// Função para acessar nome do team
char* getNome(Team* t);

// Função para acessar vitorias do team
int getVitorias(Team* t);

// Função para acessar empates do team
int getEmpates(Team* t);

// Função para acessar derrotas do team
int getDerrotas(Team* t);

// Função para acessar gols marcados do team
int getGolsMarcados(Team* t);

// Função para acessar gols sofridos do team
int getGolsSofridos(Team* t);

// Função para calcular saldo de gols do team
int getSaldoGols(Team* t);

// Função para calcular pontos ganhos do team
int getPontosGanhos(Team* t);

//funções para incrementar o número de vitórias do team
void incrementarVitorias(Team* t);

// funções para incrementar o número de empates do team
void incrementarEmpates(Team* t);

// funções para incrementar o número de derrotas do team
void incrementarDerrotas(Team* t);

// funções para incrementar o número de gols marcados do team
void incrementarGolsMarcados(Team* t, int gols);

// funções para incrementar o número de gols sofridos do team
void incrementarGolsSofridos(Team* t, int gols);

void resetarEstatisticasTeam(Team* t);

// ===================================================================

// Função para liberar memória alocada para o team
void liberarTeam(Team* t);

#endif // TEAM_H