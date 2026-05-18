#ifndef TEAM_H
#define TEAM_H

#include <assert.h>

typedef struct team Team;

Team* criarTeam(int id, const char* nome);

// ===================================================================
// FUNÇÕES GET PARA ACESSAR OS ATRIBUTOS DO TIME

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

// ===================================================================

// Função para liberar memória alocada para o time
void liberarTeam(Team* t);

#endif // TEAM_H