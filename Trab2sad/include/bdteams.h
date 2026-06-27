#ifndef BDTEAMS_H
#define BDTEAMS_H

#include <assert.h>

#include "team.h"
#include "partida.h"

typedef struct bdpartidas BDPartidas;

typedef struct bdteams BDTeams;

// Cria banco de dados de times
BDTeams* criarBDTeams();

// Cria banco de dados de times a partir de um arquivo CSV
BDTeams* criarBDTeamsDeArquivo(const char* nomeArquivo);

// Recalcula as estatisticas dos times a partir de todas as partidas
void carregarDadosDePartidasEmTeams(BDTeams* bdTeams, BDPartidas* bdPartidas);

// Quantos times tem no Banco de Dados de times
int getSizeofBDTeams(BDTeams* bd);

// Função para acessar um time específico do banco de dados
Team* getTeam(BDTeams* bd, int index);

// Função para adicionar um time ao banco de dados de times
void adicionarTeam(BDTeams* bd, Team* t);

// Função para buscar um time pelo ID no banco de dados de times
Team* buscarTeamPorId(BDTeams* bd, int id);

// Atualiza os dados dos times envolvidos em uma partida
void carregarDadosEmTeams(BDTeams* bd, Partida* p);

// Função para buscar times pelo nome ou prefixo no banco de dados de times
BDTeams* buscarPorTeamNoBD(BDTeams* bd, char* prefixo);

// Salva a tabela de classificacao ordenada em arquivo CSV
int salvarClassificacaoEmArquivo(BDTeams* bd, const char* nomeArquivo);

// Função para liberar memória alocada para o banco de dados de times
void liberarBDTeams(BDTeams* bd);

// Libera o banco de dados sem liberar os times individuais
void liberarBDTeamsAux(BDTeams* bd);

#endif // BDTEAMS_H
