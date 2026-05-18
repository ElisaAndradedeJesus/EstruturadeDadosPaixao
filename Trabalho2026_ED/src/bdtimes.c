#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "team.h"
#include "bdteams.h"

struct bdteams{
    int nElementos; //número de elementos atualmente na lista
    int capacidade; //capacidade máxima da lista
    Team** teams; //array de ponteiros para os teams
};

BDTeams* criarBDTeams() {
    BDTeams* bd = (BDTeams*)malloc(sizeof(BDTeams));
    if (bd == NULL) {
        printf("Erro ao alocar memória para o banco de dados de times.\n");
        return NULL;
    }
    bd->nElementos = 0;
    bd->capacidade = 10; // Capacidade inicial, pode ser ajustada conforme necessário
    bd->teams = (Team**)malloc(bd->capacidade * sizeof(Team*));
    if (bd->teams == NULL) {
        fprintf(stderr, "Erro ao alocar memória para os times no banco de dados.\n");
        free(bd);
        return NULL;
    }
    return bd;
}

//Função para almentar a capacidade do banco de dados de times
static int reallocateBDTeams(BDTeams* bd) {
    Team** temp = (Team**)realloc(bd->teams, bd->capacidade * 2 * sizeof(Team*));

    // Verifica se a realocação foi bem-sucedida
    if (temp == NULL) {
        printf("Erro ao realocar memória para os times no banco de dados.\n");
        return 0;
    }
    bd->teams = temp;
    bd->capacidade *= 2;
    return 1;
}

//cria Vetor de um arquivo externo
BDTeams* criarBDTeamsDeArquivo(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return NULL;
    }

    BDTeams* bd = criarBDTeams();  // Cria um banco de dados com capacidade inicial
    if (bd == NULL) {
        fclose(arquivo);
        return NULL;
    }

    // pula cabeçalho do arquivo
    char linha[100];
    fgets(linha, sizeof(linha), arquivo);

    // Lê os dados do arquivo e adiciona os times ao banco de dados
    int id;
    char nomeTime[50];
    while (fscanf(arquivo, " %d,%49[^\n]", &id, nomeTime) == 2) {
        Team* t = criarTime(id, nomeTime);
        if (t == NULL) {
            liberarBDTeams(bd);
            fclose(arquivo);
            return NULL;
        }
        if(bd->nElementos < bd->capacidade){
            // Adiciona o time ao banco de dados
            bd->teams[bd->nElementos++] = t;

        }else{
            int sucesso = reallocateBDTeams(bd);
            if(sucesso == 1){
                // Adiciona o time ao banco de dados
                bd->teams[bd->nElementos++] = t;
            }else{
                liberarBDTeams(bd);
                fclose(arquivo);
                return NULL;
            }
        }
        

    }

    fclose(arquivo);
    return bd;
}

// Função para liberar memória alocada para o banco de dados de times
void liberarBDTeams(BDTeams* bd) {
    if (bd != NULL) {
        for (int i = 0; i < bd->nElementos; i++) {
            liberarTime(bd->teams[i]);
        }
        free(bd->teams);
        free(bd);
    }
}