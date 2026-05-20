#ifndef BDTEAMS_H
#define BDTEAMS_H

#include <assert.h>

#include "team.h"
#include "partida.h"


typedef struct bdteams BDTeams;
typedef struct bdpartidas BDPartidas; // forward declaration

// cria Vetor de times
BDTeams* criarBDTeams();

//cria Vetor de um arquivo externo
BDTeams* criarBDTeamsDeArquivo(const char* nomeArquivo);

// QUantos times tem no Banco de Dados de times 
int getSizeofBDTeams(BDTeams* bd);

// Função para acessar um time específico do banco de dados
Team* getTeam(BDTeams* bd, int index);

// Função para adicionar um time ao banco de dados de times
void adicionarTeam(BDTeams* bd, Team* t);

// Função para buscar um time pelo ID no banco de dados de times
// É uma função auxiliar para facilitar a atualização dos dados dos times com base nas partidas
Team* buscarTeamPorId(BDTeams* bd, int id);

//Pega os Dados de uma partida e atualiza os dados dos times envolvidos na partida, como vitórias, empates, derrotas, gols marcados e gols sofridos
// Função auxiliar de carregarDadosDePartidasEmTimes, que é a função principal para carregar os dados de todas as partidas e atualizar os dados dos times no banco de dados de times
void carregarDadosEmTimes(BDTeams* bd, Partida* p);

// Função para buscar times pelo nome ou prefixo no banco de dados de times
BDTeams* buscarPorTeamNoBD(BDTeams* bd, char* prefixo);

// Função para liberar memória alocada para o banco de dados de times
void liberarBDTeams(BDTeams* bd);

// Função para liberar memória alocada para o banco de dados de times, sem liberar os times individuais
// (útil para casos onde os times são compartilhados entre diferentes bancos de dados)
void liberarBDTeamsAux(BDTeams* bd);

#endif // BDTEAMS_H