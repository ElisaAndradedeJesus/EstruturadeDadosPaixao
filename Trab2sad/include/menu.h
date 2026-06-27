#ifndef MENU_H
#define MENU_H

#include <assert.h>

#include "team.h"
#include "bdteams.h"

#include "partida.h"
#include "bdpartidas.h"



// Imprime o menu inicial do programa
void interfaceUser();

// Função para limpar a tela. Pra evitar que o menu fique poluído com as informações das consultas e atualizações
void limparTela();

// Função para imprimir a tabela de classificação dos times
void imprimirClassificacao(BDTeams* bd);

// Função para imprimir as partidas encontradas, mostrando o nome dos times e o resultado da partida
void printarPartidasEncontradas(BDPartidas* bdPartidas, BDTeams* bdTeams);

// Função para imprimir os times encontrados, mostrando o nome do time e suas estatísticas
void printarTeamsEncontrados(BDTeams* bd);

// Função para consultar times encontrados, mostrando o nome do time e suas estatísticas
void consultarTeamsEncontrados(BDTeams* bd);

// Função para consultar partidas
void consultarPartida(BDPartidas* bdPartidas, BDTeams* bdTeams);

// Função para atualizar partida
void atualizarPartidaMenu(BDPartidas* bdPartidas, BDTeams* bdTeams, const char* arquivoPartidas, const char* arquivoClassificacao);

// Função para remover partida
void removerPartidaMenu(BDPartidas* bdPartidas, BDTeams* bdTeams, const char* arquivoPartidas, const char* arquivoClassificacao);

// Função para inserir partida
void inserirPartidaMenu(BDPartidas* bdPartidas, BDTeams* bdTeams, const char* arquivoPartidas, const char* arquivoClassificacao);

#endif // MENU_H
