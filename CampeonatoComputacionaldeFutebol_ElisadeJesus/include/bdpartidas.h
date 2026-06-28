#ifndef BDPARTIDAS_H
#define BDPARTIDAS_H

#include <assert.h>

#include "team.h"
#include "partida.h"


typedef struct bdpartidas BDPartidas;
typedef struct bdteams BDTeams;

// Função para criar um banco de dados de partidas
BDPartidas *criarBDPartidas();

// insere uma partida no banco de dados
int adicionarPartida(BDPartidas* bd, Partida* partida);

//cria Vetor de um arquivo externo
BDPartidas* criarBDPartidasDeArquivo(const char* nomeArquivo);

// Função para saber o tamanho do banco de dados de partidas
int getSizeofBDPartidas(BDPartidas* bd);

// Função para acessar uma partida específica do banco de dados
Partida* getPartida(BDPartidas* bd, int index);

// Função para buscar partidas onde o team mandante tem um nome que corresponde ao prefixo fornecido
BDPartidas* buscarPartidaPorNomeTeamMandante(BDPartidas* bdPartidas, char* prefixo, BDTeams* bdTeams);

// Função para buscar partidas onde o team visitante tem um nome que corresponde ao prefixo fornecido
BDPartidas* buscarPartidaPorNomeTeamVisitante(BDPartidas* bdPartidas, char* prefixo, BDTeams* bdTeams);

// Função para liberar memória alocada para o banco de dados de partidas
void liberarBDPartidas(BDPartidas* bd);

// Função para liberar memória alocada para o banco de dados de partidas, sem liberar as partidas individuais
// (útil para casos onde as partidas são compartilhadas entre diferentes bancos de dados)
void liberarBDPartidasAux(BDPartidas* bd);

#endif // BDPARTIDAS_H