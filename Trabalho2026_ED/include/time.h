#ifndef TIME_H
#define TIME_H

#include <assert.h>

typedef struct team Time;

Time* criarTime(int id, const char* nome);

// ===================================================================
// FUNÇÕES GET PARA ACESSAR OS ATRIBUTOS DO TIME

// Função para acessar Id do time
int getIdTime(Time* t);

// Função para acessar nome do time
char* getNome(Time* t);

// Função para acessar vitorias do time
int getVitorias(Time* t);

// Função para acessar empates do time
int getEmpates(Time* t);

// Função para acessar derrotas do time
int getDerrotas(Time* t);

// Função para acessar gols marcados do time
int getGolsMarcados(Time* t);

// Função para acessar gols sofridos do time
int getGolsSofridos(Time* t);

// ===================================================================

// Função para liberar memória alocada para o time
void liberarTime(Time* t);

#endif // TIME_H