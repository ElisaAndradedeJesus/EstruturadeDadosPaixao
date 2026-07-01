#ifndef MENU_H
#define MENU_H

#include <assert.h>

#include "team.h"
#include "bdteams.h"

#include "partida.h"
#include "bdpartidas.h"

#include "classificacao.h"



//Conjunto de printes pra fazer a telinha inicial do programa
void interfaceUser();

// Função para limpar a tela. Pra evitar que o menu fique poluído com as informações das consultas e atualizações
void limparTela();

// Função para imprimir a tabela de classificação dos teams
void imprimirTabelaClassificacao(Classificacao* classificacao);

// Função para imprimir as partidas encontradas, mostrando o nome dos teams e o resultado da partida
void printarPartidasEncontradas(BDPartidas* bdPartidas, BDTeams* bdTeams);

// Função para imprimir os teams encontrados, mostrando o nome do team e suas estatísticas
void printarTeamsEncontrados(BDTeams* bd);

// Função para consultar teams encontrados, mostrando o nome do team e suas estatísticas
void consultarTeamsEncontrados(BDTeams* bd);

// Função para consultar partidas
void consultarPartida(BDPartidas* bdPartidas, BDTeams* bdTeams);

#endif // MENU_H