#ifndef BDTEAMS_H
#define BDTEAMS_H

#include <assert.h>

#include "team.h"

typedef struct bdteams BDTeams;

// cria Vetor de times
BDTeams* criarBDTeams();

//cria Vetor de um arquivo externo
BDTeams* criarBDTeamsDeArquivo(const char* nomeArquivo);

// QUantos times tem no Banco de Dados de times 
int getSizeofBDTeams(BDTeams* bd);

// Função para acessar um time específico do banco de dados
Team* getTeam(BDTeams* bd, int index);

// Função para liberar memória alocada para o banco de dados de times
void liberarBDTeams(BDTeams* bd);

#endif // BDTEAMS_H