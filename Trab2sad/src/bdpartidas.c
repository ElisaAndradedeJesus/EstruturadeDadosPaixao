#include <stdio.h>
#include <stdlib.h>

#include "team.h"
#include "partida.h"
#include "bdteams.h"
#include "bdpartidas.h"

typedef struct noPartida {
    Partida* partida;
    struct noPartida* proximo;
} NoPartida;

struct bdpartidas {
    int nElementos;
    NoPartida* inicio;
    NoPartida* fim;
};

BDPartidas* criarBDPartidas() {
    BDPartidas* bd = (BDPartidas*)malloc(sizeof(BDPartidas));
    if (bd == NULL) {
        printf("Erro ao alocar memória para o banco de dados de partidas.\n");
        return NULL;
    }

    bd->nElementos = 0;
    bd->inicio = NULL;
    bd->fim = NULL;
    return bd;
}

int adicionarPartida(BDPartidas* bd, Partida* partida) {
    if (bd == NULL || partida == NULL) {
        return 0;
    }

    NoPartida* novo = (NoPartida*)malloc(sizeof(NoPartida));
    if (novo == NULL) {
        printf("Erro ao alocar nó para a partida.\n");
        return 0;
    }

    novo->partida = partida;
    novo->proximo = NULL;

    if (bd->fim == NULL) {
        bd->inicio = novo;
        bd->fim = novo;
    } else {
        bd->fim->proximo = novo;
        bd->fim = novo;
    }

    bd->nElementos++;
    return 1;
}

BDPartidas* criarBDPartidasDeArquivo(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return NULL;
    }

    BDPartidas* bd = criarBDPartidas();
    if (bd == NULL) {
        fclose(arquivo);
        return NULL;
    }

    char linha[100];
    fgets(linha, sizeof(linha), arquivo);

    int id, time1, time2, golsTime1, golsTime2;
    while (fscanf(arquivo, " %d,%d,%d,%d,%d", &id, &time1, &time2, &golsTime1, &golsTime2) == 5) {
        Partida* partida = criarPartida(id, time1, time2, golsTime1, golsTime2);
        if (!adicionarPartida(bd, partida)) {
            liberarPartida(partida);
            liberarBDPartidas(bd);
            fclose(arquivo);
            return NULL;
        }
    }

    fclose(arquivo);
    return bd;
}

int getSizeofBDPartidas(BDPartidas* bd) {
    if (bd != NULL) {
        return bd->nElementos;
    }
    return -1;
}

Partida* getPartida(BDPartidas* bd, int index) {
    if (bd == NULL || index < 0 || index >= bd->nElementos) {
        return NULL;
    }

    NoPartida* atual = bd->inicio;
    for (int i = 0; i < index; i++) {
        atual = atual->proximo;
    }
    return atual->partida;
}

Partida* buscarPartidaPorId(BDPartidas* bd, int id) {
    if (bd == NULL) {
        return NULL;
    }

    for (NoPartida* atual = bd->inicio; atual != NULL; atual = atual->proximo) {
        if (getIdPartida(atual->partida) == id) {
            return atual->partida;
        }
    }
    return NULL;
}

int gerarProximoIdPartida(BDPartidas* bd) {
    int maiorId = -1;
    if (bd == NULL) {
        return 0;
    }

    for (NoPartida* atual = bd->inicio; atual != NULL; atual = atual->proximo) {
        if (getIdPartida(atual->partida) > maiorId) {
            maiorId = getIdPartida(atual->partida);
        }
    }
    return maiorId + 1;
}

int atualizarPlacarPartida(BDPartidas* bd, int id, int golsTime1, int golsTime2) {
    Partida* partida = buscarPartidaPorId(bd, id);
    if (partida == NULL || golsTime1 < 0 || golsTime2 < 0) {
        return 0;
    }

    setPlacarPartida(partida, golsTime1, golsTime2);
    return 1;
}

int removerPartidaPorId(BDPartidas* bd, int id) {
    if (bd == NULL) {
        return 0;
    }

    NoPartida* anterior = NULL;
    NoPartida* atual = bd->inicio;

    while (atual != NULL) {
        if (getIdPartida(atual->partida) == id) {
            if (anterior == NULL) {
                bd->inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            if (bd->fim == atual) {
                bd->fim = anterior;
            }

            liberarPartida(atual->partida);
            free(atual);
            bd->nElementos--;
            return 1;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    return 0;
}

int salvarBDPartidasEmArquivo(BDPartidas* bd, const char* nomeArquivo) {
    if (bd == NULL || nomeArquivo == NULL) {
        return 0;
    }

    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        return 0;
    }

    fprintf(arquivo, "ID,Time1,Time2,GolsTime1,GolsTime2\n");
    for (NoPartida* atual = bd->inicio; atual != NULL; atual = atual->proximo) {
        Partida* p = atual->partida;
        fprintf(arquivo, "%d,%d,%d,%d,%d\n",
            getIdPartida(p),
            getIdTeam1(p),
            getIdTeam2(p),
            getGolsTeam1(p),
            getGolsTeam2(p));
    }

    fclose(arquivo);
    return 1;
}

BDPartidas* buscarPartidaPorNomeTeamMandante(BDPartidas* bdPartidas, char* prefixo, BDTeams* bdTeams) {
    BDPartidas* partidasEncontradas = criarBDPartidas();
    BDTeams* timesComPrefixo = buscarPorTeamNoBD(bdTeams, prefixo);

    if (partidasEncontradas == NULL || timesComPrefixo == NULL) {
        liberarBDPartidasAux(partidasEncontradas);
        liberarBDTeamsAux(timesComPrefixo);
        return NULL;
    }

    for (NoPartida* atual = bdPartidas->inicio; atual != NULL; atual = atual->proximo) {
        Partida* p = atual->partida;
        for (int j = 0; j < getSizeofBDTeams(timesComPrefixo); j++) {
            Team* t = getTeam(timesComPrefixo, j);
            if (getIdTeam1(p) == getIdTeam(t)) {
                if (!adicionarPartida(partidasEncontradas, p)) {
                    liberarBDPartidasAux(partidasEncontradas);
                    liberarBDTeamsAux(timesComPrefixo);
                    return NULL;
                }
            }
        }
    }

    liberarBDTeamsAux(timesComPrefixo);
    return partidasEncontradas;
}

BDPartidas* buscarPartidaPorNomeTeamVisitante(BDPartidas* bdPartidas, char* prefixo, BDTeams* bdTeams) {
    BDPartidas* partidasEncontradas = criarBDPartidas();
    BDTeams* timesComPrefixo = buscarPorTeamNoBD(bdTeams, prefixo);

    if (partidasEncontradas == NULL || timesComPrefixo == NULL) {
        liberarBDPartidasAux(partidasEncontradas);
        liberarBDTeamsAux(timesComPrefixo);
        return NULL;
    }

    for (NoPartida* atual = bdPartidas->inicio; atual != NULL; atual = atual->proximo) {
        Partida* p = atual->partida;
        for (int j = 0; j < getSizeofBDTeams(timesComPrefixo); j++) {
            Team* t = getTeam(timesComPrefixo, j);
            if (getIdTeam2(p) == getIdTeam(t)) {
                if (!adicionarPartida(partidasEncontradas, p)) {
                    liberarBDPartidasAux(partidasEncontradas);
                    liberarBDTeamsAux(timesComPrefixo);
                    return NULL;
                }
            }
        }
    }

    liberarBDTeamsAux(timesComPrefixo);
    return partidasEncontradas;
}

void liberarBDPartidas(BDPartidas* bd) {
    if (bd != NULL) {
        NoPartida* atual = bd->inicio;
        while (atual != NULL) {
            NoPartida* proximo = atual->proximo;
            liberarPartida(atual->partida);
            free(atual);
            atual = proximo;
        }
        free(bd);
    }
}

void liberarBDPartidasAux(BDPartidas* bd) {
    if (bd != NULL) {
        NoPartida* atual = bd->inicio;
        while (atual != NULL) {
            NoPartida* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
        free(bd);
    }
}
