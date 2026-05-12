#ifndef BDPARTIDAS_H
#define BDPARTIDAS_H

#include <assert.h>

#include "partida.h"

typedef struct bdpartidas BDPartidas;

// Função para criar um banco de dados de partidas
BDPartidas *criarBDPartidas();

// insere uma partida no banco de dados
int adicionarPartida(BDPartidas* bd, Partida* partida);

//cria Vetor de um arquivo externo
BDPartidas* criarBDPartidasDeArquivo(const char* nomeArquivo);

// Função para liberar memória alocada para o banco de dados de partidas
void liberarBDPartidas(BDPartidas* bd);

#endif // BDPARTIDAS_H