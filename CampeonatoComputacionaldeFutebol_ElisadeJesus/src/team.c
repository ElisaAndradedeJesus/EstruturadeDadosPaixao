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

Team* criarTeam(int id, const char* nome){
    Team* t = (Team*)malloc(sizeof(Team));
    if (t == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o team.\n");
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

// Função para acessar Id do team
int getIdTeam(Team* t) {
    if (t!= NULL) {
        return t->id;
    }
    return -1;  // Valor inválido se o team for NULL
}

// Função para acessar nome do team
char* getNome(Team* t) {
    if(t != NULL) {
        return t->nome;
    }
    return NULL;
}

// Função para acessar vitorias do team
int getVitorias(Team* t) {
    if (t != NULL) {
        return t->vitorias;
    }
    return -1;  // Valor inválido se o team for NULL
}

// Função para acessar empates do team
int getEmpates(Team* t) {
    if (t != NULL) {
        return t->empates;
    }
    return -1;  // Valor inválido se o team for NULL
}

// Função para acessar derrotas do team
int getDerrotas(Team* t) {
    if (t != NULL) {
        return t->derrotas;
    }
    return -1;  // Valor inválido se o team for NULL
}

// Função para acessar gols marcados do team
int getGolsMarcados(Team* t) {
    if(t != NULL) {
        return t->golsMarcados;
    }
    return -1;  // Valor inválido se o team for NULL
}

// Função para acessar gols sofridos do team
int getGolsSofridos(Team* t) {
    if(t != NULL) {
        return t->golsSofridos;
    }
    return -1;  // Valor inválido se o team for NULL
}

// Função para calcular saldo de gols do team
int getSaldoGols(Team* t) {
    if (t != NULL) {
        return t->golsMarcados - t->golsSofridos;
    }
    return -999;  // Valor inválido se o team for NULL
}

// Função para calcular pontos ganhos do team
int getPontosGanhos(Team* t) {
    if (t != NULL) {
        return t->vitorias * 3 + t->empates; // 3 pontos por vitória e 1 ponto por empate
    }
    return -999;  // Valor inválido se o team for NULL
}

//funções para incrementar o número de vitórias do team
void incrementarVitorias(Team* t) {
    if (t != NULL) {
        t->vitorias++;
    } else {
        printf("Erro: Team é NULL. Não é possível incrementar vitórias.\n");
    }
}

// funções para incrementar o número de empates do team
void incrementarEmpates(Team* t) {
    if (t != NULL) {
        t->empates++;
    } else {
        printf("Erro: Team é NULL. Não é possível incrementar empates.\n");
    }
}

// funções para incrementar o número de derrotas do team
void incrementarDerrotas(Team* t) {
    if (t != NULL) {
        t->derrotas++;
    } else {
        printf("Erro: Team é NULL. Não é possível incrementar derrotas.\n");
    }
}

// funções para incrementar o número de gols marcados do team
void incrementarGolsMarcados(Team* t, int gols) {
    if (t != NULL) {
        t->golsMarcados += gols;
    } else {
        printf("Erro: Team é NULL. Não é possível incrementar gols marcados.\n");
    }
}

// funções para incrementar o número de gols sofridos do team
void incrementarGolsSofridos(Team* t, int gols) {
    if (t != NULL) {
        t->golsSofridos += gols;
    } else {
        printf("Erro: Team é NULL. Não é possível incrementar gols sofridos.\n");
    }
}

// Função para liberar memória alocada para o team
void liberarTeam(Team* t) {
    if (t != NULL) {
        free(t);
    }
}

void resetarEstatisticasTeam(Team* t){
        if (t != NULL) {
        t->vitorias = 0;
        t->empates = 0;
        t->derrotas = 0;
        t->golsMarcados = 0;
        t->golsSofridos = 0;
    }
}