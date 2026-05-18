#ifndef BDTEAMS_H
#define BDTEAMS_H

#include <assert.h>

#include "team.h"

typedef struct bdteam BDTeams;

// cria Vetor de times
BDTeams* criarBDTeams();

//cria Vetor de um arquivo externo
BDTeams* criarBDTeamsDeArquivo(const char* nomeArquivo);

// Função para liberar memória alocada para o banco de dados de times
void liberarBDTeams(BDTeams* bd);

#endif // BDTEAMS_H