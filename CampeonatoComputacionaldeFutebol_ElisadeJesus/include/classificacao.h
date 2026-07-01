#ifndef CLASSIFICACAO_H
#define CLASSIFICACAO_H

#include <assert.h>

#include "team.h"
#include "partida.h"
#include "bdteams.h"


typedef struct  classificacao Classificacao;

// Ordena a classificação de forma decrescente (do com melhor classificação pro menos classificado)
void ordenarClassificacao(Classificacao* classificacao);

// Função para criar uma nova classificação e carregar os dados da classificação
Classificacao* gerarClassificacao(BDTeams* bdTeams);

// Função para imprimir a tabela de classificação dos times
void imprimirClassificacao(Classificacao* classificacao);

// Função para liberar memória alocada para a classificação
void liberarClassificacao(Classificacao* classificacao);

// Função para atualizar a classificação com os dados mais recentes
Classificacao* atualizarClassificacao(Classificacao* classificacao, BDTeams* bdTeams);

// Função para salvar a classificação em um arquivo 
int salvarClassificacaoEmArquivo(Classificacao* classificacao, const char* nomeArquivo);

#endif // classificacao.h