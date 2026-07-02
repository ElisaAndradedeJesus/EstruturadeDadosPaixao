#ifndef BDTEAMS_H
#define BDTEAMS_H

#include <assert.h>

#include "team.h"
#include "partida.h"


typedef struct bdteams BDTeams;
typedef struct bdpartidas BDPartidas;

// cria Vetor de teams
BDTeams* criarBDTeams();

//cria Vetor de um arquivo externo
BDTeams* criarBDTeamsDeArquivo(const char* nomeArquivo);

// Função para carregar os dados de todas as partidas e atualizar os dados dos teams no banco de dados de teams 
// só pode ser executada 1 vez a n ser que eu crie alguma forma de resertar os dados dos teams.
void carregarDadosDePartidasEmTeams(BDTeams* bdTeams, BDPartidas* bdPartidas);

// QUantos teams tem no Banco de Dados de teams 
int getSizeofBDTeams(BDTeams* bd);

// Função para acessar um team específico do banco de dados
Team* getTeam(BDTeams* bd, int index);

// Função para adicionar um team ao banco de dados de teams
void adicionarTeam(BDTeams* bd, Team* t);

// Função para buscar um team pelo ID no banco de dados de teams
// É uma função auxiliar para facilitar a atualização dos dados dos teams com base nas partidas
Team* buscarTeamPorId(BDTeams* bd, int id);

//Pega os Dados de uma partida e atualiza os dados dos teams envolvidos na partida, como vitórias, empates, derrotas, gols marcados e gols sofridos
// Função auxiliar de carregarDadosDePartidasEmTeams, que é a função principal para carregar os dados de todas as partidas e atualizar os dados dos teams no banco de dados de teams
void carregarDadosEmTeams(BDTeams* bd, Partida* p);

// Função para buscar teams pelo nome ou prefixo no banco de dados de teams
BDTeams* buscarPorTeamNoBD(BDTeams* bd, char* prefixo);

// Função para liberar memória alocada para o banco de dados de teams
void liberarBDTeams(BDTeams* bd);

// Função para liberar memória alocada para o banco de dados de teams, sem liberar os teams individuais
// (útil para casos onde os teams são compartilhados entre diferentes bancos de dados)
void liberarBDTeamsAux(BDTeams* bd);

// Recalcula as estatísticas dos teams a partir da lista atual de partidas.
// Primeiro zera os dados acumulados para evitar contagem duplicada quando
// uma partida é inserida, removida ou atualizada.
void atualizarDadosTeam(BDTeams* bdTeams, BDPartidas* bdPartidas);

#endif // BDTEAMS_H