#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "team.h"
#include "partida.h"
#include "bdteams.h"
#include "bdpartidas.h"

typedef struct noTime {
    Team* time;
    struct noTime* proximo;
} NoTime;

struct bdteams {
    int nElementos;
    NoTime* inicio;
    NoTime* fim;
};

static int prefixoIgualIgnoreCase(const char* texto, const char* prefixo) {
    while (*prefixo != '\0') {
        if (*texto == '\0') {
            return 0;
        }
        if (tolower((unsigned char)*texto) != tolower((unsigned char)*prefixo)) {
            return 0;
        }
        texto++;
        prefixo++;
    }
    return 1;
}

static int compararTimes(const void* a, const void* b) {
    Team* timeA = *(Team**)a;
    Team* timeB = *(Team**)b;

    if (getPontosGanhos(timeA) != getPontosGanhos(timeB)) {
        return getPontosGanhos(timeB) - getPontosGanhos(timeA);
    }
    if (getVitorias(timeA) != getVitorias(timeB)) {
        return getVitorias(timeB) - getVitorias(timeA);
    }
    if (getSaldoGols(timeA) != getSaldoGols(timeB)) {
        return getSaldoGols(timeB) - getSaldoGols(timeA);
    }
    if (getGolsMarcados(timeA) != getGolsMarcados(timeB)) {
        return getGolsMarcados(timeB) - getGolsMarcados(timeA);
    }
    return getIdTeam(timeA) - getIdTeam(timeB);
}

static Team** criarVetorOrdenado(BDTeams* bd) {
    if (bd == NULL || bd->nElementos == 0) {
        return NULL;
    }

    Team** vetor = (Team**)malloc(bd->nElementos * sizeof(Team*));
    if (vetor == NULL) {
        return NULL;
    }

    NoTime* atual = bd->inicio;
    for (int i = 0; i < bd->nElementos; i++) {
        vetor[i] = atual->time;
        atual = atual->proximo;
    }

    qsort(vetor, bd->nElementos, sizeof(Team*), compararTimes);
    return vetor;
}

BDTeams* criarBDTeams() {
    BDTeams* bd = (BDTeams*)malloc(sizeof(BDTeams));
    if (bd == NULL) {
        printf("Erro ao alocar memória para o banco de dados de times.\n");
        return NULL;
    }

    bd->nElementos = 0;
    bd->inicio = NULL;
    bd->fim = NULL;
    return bd;
}

void adicionarTeam(BDTeams* bd, Team* t) {
    if (bd == NULL || t == NULL) {
        printf("Erro: banco de dados ou time inválido.\n");
        return;
    }

    NoTime* novo = (NoTime*)malloc(sizeof(NoTime));
    if (novo == NULL) {
        printf("Erro ao alocar nó para o time.\n");
        return;
    }

    novo->time = t;
    novo->proximo = NULL;

    if (bd->fim == NULL) {
        bd->inicio = novo;
        bd->fim = novo;
    } else {
        bd->fim->proximo = novo;
        bd->fim = novo;
    }

    bd->nElementos++;
}

BDTeams* criarBDTeamsDeArquivo(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return NULL;
    }

    BDTeams* bd = criarBDTeams();
    if (bd == NULL) {
        fclose(arquivo);
        return NULL;
    }

    char linha[100];
    fgets(linha, sizeof(linha), arquivo);

    int id;
    char nomeTime[50];
    while (fscanf(arquivo, " %d,%49[^\n]", &id, nomeTime) == 2) {
        Team* t = criarTeam(id, nomeTime);
        adicionarTeam(bd, t);
    }

    fclose(arquivo);
    return bd;
}

void carregarDadosDePartidasEmTeams(BDTeams* bdTeams, BDPartidas* bdPartidas) {
    if (bdTeams == NULL || bdPartidas == NULL) {
        return;
    }

    for (NoTime* atual = bdTeams->inicio; atual != NULL; atual = atual->proximo) {
        resetarEstatisticasTeam(atual->time);
    }

    for (int i = 0; i < getSizeofBDPartidas(bdPartidas); i++) {
        Partida* p = getPartida(bdPartidas, i);
        carregarDadosEmTeams(bdTeams, p);
    }
}

int getSizeofBDTeams(BDTeams* bd) {
    assert(bd != NULL);
    return bd->nElementos;
}

Team* getTeam(BDTeams* bd, int index) {
    assert(bd != NULL);
    assert(index >= 0 && index < bd->nElementos);

    NoTime* atual = bd->inicio;
    for (int i = 0; i < index; i++) {
        atual = atual->proximo;
    }
    return atual->time;
}

Team* buscarTeamPorId(BDTeams* bd, int id) {
    if (bd == NULL) {
        return NULL;
    }

    for (NoTime* atual = bd->inicio; atual != NULL; atual = atual->proximo) {
        if (getIdTeam(atual->time) == id) {
            return atual->time;
        }
    }
    return NULL;
}

void carregarDadosEmTeams(BDTeams* bd, Partida* p) {
    if (bd == NULL || p == NULL) {
        return;
    }

    Team* time1 = buscarTeamPorId(bd, getIdTeam1(p));
    Team* time2 = buscarTeamPorId(bd, getIdTeam2(p));

    if (time1 == NULL || time2 == NULL) {
        return;
    }

    int golsTime1 = getGolsTeam1(p);
    int golsTime2 = getGolsTeam2(p);

    if (golsTime1 > golsTime2) {
        incrementarVitorias(time1);
        incrementarDerrotas(time2);
    } else if (golsTime1 < golsTime2) {
        incrementarDerrotas(time1);
        incrementarVitorias(time2);
    } else {
        incrementarEmpates(time1);
        incrementarEmpates(time2);
    }

    incrementarGolsMarcados(time1, golsTime1);
    incrementarGolsSofridos(time1, golsTime2);
    incrementarGolsMarcados(time2, golsTime2);
    incrementarGolsSofridos(time2, golsTime1);
}

BDTeams* buscarPorTeamNoBD(BDTeams* bd, char* prefixo) {
    BDTeams* resultados = criarBDTeams();
    if (bd == NULL || resultados == NULL || prefixo == NULL) {
        return resultados;
    }

    for (NoTime* atual = bd->inicio; atual != NULL; atual = atual->proximo) {
        if (prefixoIgualIgnoreCase(getNome(atual->time), prefixo)) {
            adicionarTeam(resultados, atual->time);
        }
    }
    return resultados;
}

int salvarClassificacaoEmArquivo(BDTeams* bd, const char* nomeArquivo) {
    if (bd == NULL || nomeArquivo == NULL) {
        return 0;
    }

    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        return 0;
    }

    fprintf(arquivo, "ID,Time,V,E,D,GM,GS,S,PG\n");
    Team** ordenados = criarVetorOrdenado(bd);
    for (int i = 0; i < bd->nElementos; i++) {
        Team* t = ordenados[i];
        fprintf(arquivo, "%d,%s,%d,%d,%d,%d,%d,%d,%d\n",
            getIdTeam(t),
            getNome(t),
            getVitorias(t),
            getEmpates(t),
            getDerrotas(t),
            getGolsMarcados(t),
            getGolsSofridos(t),
            getSaldoGols(t),
            getPontosGanhos(t));
    }

    free(ordenados);
    fclose(arquivo);
    return 1;
}

void liberarBDTeams(BDTeams* bd) {
    if (bd != NULL) {
        NoTime* atual = bd->inicio;
        while (atual != NULL) {
            NoTime* proximo = atual->proximo;
            liberarTeam(atual->time);
            free(atual);
            atual = proximo;
        }
        free(bd);
    }
}

void liberarBDTeamsAux(BDTeams* bd) {
    if (bd != NULL) {
        NoTime* atual = bd->inicio;
        while (atual != NULL) {
            NoTime* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
        free(bd);
    }
}
