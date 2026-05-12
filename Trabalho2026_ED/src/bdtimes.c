#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "time.h"
#include "bdtimes.h"

struct bdteam{
    int nElementos; //número de elementos atualmente na lista
    int capacidade; //capacidade máxima da lista
    Time** times; //array de ponteiros para os times
};

BDTimes* criarBDTimes() {
    BDTimes* bd = (BDTimes*)malloc(sizeof(BDTimes));
    if (bd == NULL) {
        printf("Erro ao alocar memória para o banco de dados de times.\n");
        return NULL;
    }
    bd->nElementos = 0;
    bd->capacidade = 10; // Capacidade inicial, pode ser ajustada conforme necessário
    bd->times = (Time**)malloc(bd->capacidade * sizeof(Time*));
    if (bd->times == NULL) {
        fprintf(stderr, "Erro ao alocar memória para os times no banco de dados.\n");
        free(bd);
        return NULL;
    }
    return bd;
}

//Função para almentar a capacidade do banco de dados de times
static int reallocateBDTimes(BDTimes* bd) {
    Time** temp = (Time**)realloc(bd->times, bd->capacidade * 2 * sizeof(Time*));
 
    // Verifica se a realocação foi bem-sucedida
    if (temp == NULL) {
        printf("Erro ao realocar memória para os times no banco de dados.\n");
        return 0;
    }
    bd->times = temp;
    bd->capacidade *= 2;
    return 1;
}

//cria Vetor de um arquivo externo
BDTimes* criarBDTimesDeArquivo(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return NULL;
    }

    BDTimes* bd = criarBDTimes();  // Cria um banco de dados com capacidade inicial
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
        Time* t = criarTime(id, nomeTime);
        if (t == NULL) {
            liberarBDTimes(bd);
            fclose(arquivo);
            return NULL;
        }
        if(bd->nElementos < bd->capacidade){
            // Adiciona o time ao banco de dados
            bd->times[bd->nElementos++] = t;

        }else{
            int sucesso = reallocateBDTimes(bd);
            if(sucesso == 1){
                // Adiciona o time ao banco de dados
                bd->times[bd->nElementos++] = t;
            }else{
                liberarBDTimes(bd);
                fclose(arquivo);
                return NULL;
            }
        }
        

    }

    fclose(arquivo);
    return bd;
}

// Função para liberar memória alocada para o banco de dados de times
void liberarBDTimes(BDTimes* bd) {
    if (bd != NULL) {
        for (int i = 0; i < bd->nElementos; i++) {
            liberarTime(bd->times[i]);
        }
        free(bd->times);
        free(bd);
    }
}