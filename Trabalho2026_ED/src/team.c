#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "team.h"

struct team{
    int id;
    char nome[50];

    int vitorias;
    int empates;
    int derrotas;

    int golsMarcados;
    int golsSofridos;
};

Team* criarTime(int id, const char* nome){
    Team* t = (Team*)malloc(sizeof(Team));
    if (t == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o time.\n");
        exit(EXIT_FAILURE);
    }
    t->id = id;
    snprintf(t->nome, sizeof(t->nome), "%s", nome);
    t->vitorias = 0;
    t->empates = 0;
    t->derrotas = 0;
    t->golsMarcados = 0;
    t->golsSofridos = 0;
    return t;
}

// Função para acessar Id do time
int getIdTeam(Team* t) {
    assert(t != NULL);
    return t->id;
}

// Função para acessar nome do time
char* getNome(Team* t) {
    assert(t != NULL);
    return t->nome;
}

// Função para acessar vitorias do time
int getVitorias(Team* t) {
    assert(t != NULL);
    return t->vitorias;
}

// Função para acessar empates do time
int getEmpates(Team* t) {
    assert(t != NULL);
    return t->empates;
}

// Função para acessar derrotas do time
int getDerrotas(Team* t) {
    assert(t != NULL);
    return t->derrotas;
}

// Função para acessar gols marcados do time
int getGolsMarcados(Team* t) {
    assert(t != NULL);
    return t->golsMarcados;
}

// Função para acessar gols sofridos do time
int getGolsSofridos(Team* t) {
    assert(t != NULL);
    return t->golsSofridos;
}

// Função para liberar memória alocada para o time
void liberarTime(Team* t) {
    if (t != NULL) {
        free(t);
    }
}

