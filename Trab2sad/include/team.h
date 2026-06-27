#ifndef TEAM_H
#define TEAM_H

#include <assert.h>

typedef struct team Team;

Team* criarTeam(int id, const char* nome);

// ===================================================================

// Função para acessar Id do time
int getIdTeam(Team* t);

// Função para acessar nome do time
char* getNome(Team* t);

// Função para acessar vitorias do time
int getVitorias(Team* t);

// Função para acessar empates do time
int getEmpates(Team* t);

// Função para acessar derrotas do time
int getDerrotas(Team* t);

// Função para acessar gols marcados do time
int getGolsMarcados(Team* t);

// Função para acessar gols sofridos do time
int getGolsSofridos(Team* t);

// Função para calcular saldo de gols do time
int getSaldoGols(Team* t);

// Função para calcular pontos ganhos do time
int getPontosGanhos(Team* t);

// Reinicia as estatisticas calculadas do time
void resetarEstatisticasTeam(Team* t);

//funções para incrementar o número de vitórias do time
void incrementarVitorias(Team* t);

// funções para incrementar o número de empates do team
void incrementarEmpates(Team* t);

// funções para incrementar o número de derrotas do team
void incrementarDerrotas(Team* t);

// funções para incrementar o número de gols marcados do team
void incrementarGolsMarcados(Team* t, int gols);

// funções para incrementar o número de gols sofridos do team
void incrementarGolsSofridos(Team* t, int gols);

// ===================================================================

// Função para liberar memória alocada para o time
void liberarTeam(Team* t);

#endif // TEAM_H
