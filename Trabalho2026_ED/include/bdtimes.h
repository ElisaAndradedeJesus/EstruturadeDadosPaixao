#ifndef BDTIMES_H
#define BDTIMES_H

#include <assert.h>

#include "time.h"

typedef struct bdteam BDTimes;

// cria Vetor de times
BDTimes* criarBDTimes();

//cria Vetor de um arquivo externo
BDTimes* criarBDTimesDeArquivo(const char* nomeArquivo);

// Função para liberar memória alocada para o banco de dados de times
void liberarBDTimes(BDTimes* bd);

#endif // BDTIMES_H