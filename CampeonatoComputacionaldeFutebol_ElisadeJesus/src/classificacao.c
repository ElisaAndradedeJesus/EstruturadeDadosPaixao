#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <strings.h>

#include "team.h"
#include "partida.h"
#include "bdteams.h"
#include "bdpartidas.h"
#include "classificacao.h"


typedef struct Info {
    int id;
    char nome[50];

    int vitorias;
    int empates;
    int derrotas;
    int golsMarcados;
    int golsSofridos;
    int saldoDeGols;
    int pontosGanhos;
} Info;

typedef struct ClassificacaoNode {
    Info info;
    struct ClassificacaoNode* proximo;
} ClassificacaoNode;


struct classificacao{
    int nElementos; //número de elementos atualmente na lista
    struct ClassificacaoNode* primeiro;
    struct ClassificacaoNode* ultimo;
};



Classificacao* criarClassificacao() {
    Classificacao* classificacao = (Classificacao*)malloc(sizeof(Classificacao));
    if (classificacao == NULL) {
        printf("Erro ao alocar memória para a classificação.\n");
        return NULL;
    }
    classificacao->nElementos = 0;
    classificacao->primeiro = NULL;
    classificacao->ultimo = NULL;
    return classificacao;
}

// Define os critérios de ordenação da classificação.
// A ordem segue o enunciado: pontos ganhos, vitórias, saldo de gols,
// gols marcados e, por fim, ID como critério estável de desempate.
static int deveTrocar(Info a, Info b) {
    if (a.pontosGanhos != b.pontosGanhos) {
        return a.pontosGanhos < b.pontosGanhos;
    }

    if (a.vitorias != b.vitorias) {
        return a.vitorias < b.vitorias;
    }

    if (a.saldoDeGols != b.saldoDeGols) {
        return a.saldoDeGols < b.saldoDeGols;
    }

    if (a.golsMarcados != b.golsMarcados) {
        return a.golsMarcados < b.golsMarcados;
    }

    return a.id > b.id;
}

// Ordena a lista por bubble sort trocando apenas os dados dos nós.
// Isso evita alterar os ponteiros da lista encadeada.
void ordenarClassificacao(Classificacao* classificacao) {
    if (classificacao == NULL || classificacao->primeiro == NULL) {
        return;
    }
    int ocorreuTroca = 1;
    while (ocorreuTroca) {
        ocorreuTroca = 0;

    ClassificacaoNode* atual = classificacao->primeiro;
        while (atual->proximo != NULL) {
            if (deveTrocar(atual->info, atual->proximo->info)) {
                Info temp = atual->info;
                atual->info = atual->proximo->info;
                atual->proximo->info = temp;

                ocorreuTroca = 1;
            }
            atual = atual->proximo;
        }
    }
}


// Função para carregar os dados da classificação
Classificacao* gerarClassificacao(BDTeams* bdTeams) {
    Classificacao* classificacao = criarClassificacao();
    for (int i = 0; i < getSizeofBDTeams(bdTeams); i++) {
        Team* t = getTeam(bdTeams, i);
        Info info;
        info.id = getIdTeam(t);
        strncpy(info.nome, getNome(t), sizeof(info.nome) - 1);
        info.nome[sizeof(info.nome) - 1] = '\0';  // Garantir a terminação da string

        info.vitorias = getVitorias(t);
        info.empates = getEmpates(t);
        info.derrotas = getDerrotas(t);
        info.golsMarcados = getGolsMarcados(t);
        info.golsSofridos = getGolsSofridos(t);
        info.saldoDeGols = getSaldoGols(t);
        info.pontosGanhos = getPontosGanhos(t);

        ClassificacaoNode* novoNo = (ClassificacaoNode*)malloc(sizeof(ClassificacaoNode));
        if (novoNo == NULL) {
            printf("Erro ao alocar memória para o novo nó da classificação.\n");
            return NULL;
        }
        novoNo->info = info;
        novoNo->proximo = NULL;

        if (classificacao->primeiro == NULL) {
            classificacao->primeiro = novoNo;
            classificacao->ultimo = novoNo;
        } else {
            classificacao->ultimo->proximo = novoNo;
            classificacao->ultimo = novoNo;
        }
        classificacao->nElementos++;
    }
    ordenarClassificacao(classificacao);
    return classificacao;
}

// Função para imprimir a tabela de classificação dos teams
void imprimirClassificacao(Classificacao* classificacao) {
    if (classificacao == NULL) {
        printf("Classificação não disponível.\n");
        return;
    }
    printf("%-5s %-20s %-5s %-5s %-5s %-5s %-5s %-5s %-5s\n",
       "ID", "Team", "V", "E", "D", "GM", "GS", "S", "PG");

    ClassificacaoNode* atual = classificacao->primeiro;
    while (atual != NULL) {
        Info info = atual->info;
        printf("%-5d %-20s %-5d %-5d %-5d %-5d %-5d %-5d %-5d\n",
               info.id,
               info.nome,
               info.vitorias,
               info.empates,
               info.derrotas,
               info.golsMarcados,
               info.golsSofridos,
               info.saldoDeGols,
               info.pontosGanhos);
        atual = atual->proximo;
    }
}

int salvarClassificacaoEmArquivo(Classificacao* classificacao, const char* nomeArquivo) {

    ordenarClassificacao(classificacao);
    
    if (classificacao == NULL || nomeArquivo == NULL) {
        return 0;
    }

    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de classificação.\n");
        return 0;
    }

    fprintf(arquivo, "ID,Time,V,E,D,GM,GS,S,PG\n");

    ClassificacaoNode* atual = classificacao->primeiro;

    while (atual != NULL) {
        Info info = atual->info;

        fprintf(arquivo, "%d,%s,%d,%d,%d,%d,%d,%d,%d\n",
            info.id,
            info.nome,
            info.vitorias,
            info.empates,
            info.derrotas,
            info.golsMarcados,
            info.golsSofridos,
            info.saldoDeGols,
            info.pontosGanhos
        );

        atual = atual->proximo;
    }
    fclose(arquivo);
    return 1;
}

// Função para liberar memória alocada para a classificação
void liberarClassificacao(Classificacao* classificacao) {
    if (classificacao != NULL) {
        ClassificacaoNode* atual = classificacao->primeiro;

        while (atual != NULL) {
            ClassificacaoNode* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }

        free(classificacao);
    }
}


Classificacao* atualizarClassificacao(Classificacao* classificacao, BDTeams* bdTeams) {
    if (classificacao == NULL || bdTeams == NULL) {
        return NULL;
    }
    liberarClassificacao(classificacao);
    return gerarClassificacao(bdTeams);
}


