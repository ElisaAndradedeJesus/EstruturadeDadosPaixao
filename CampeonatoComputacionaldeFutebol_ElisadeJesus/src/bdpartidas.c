#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "team.h"
#include "partida.h"
#include "bdteams.h"
#include "bdpartidas.h"

// Nó interno da lista encadeada de partidas.
// Fica privado neste módulo para esconder a implementação do TAD BDPartidas.
typedef struct PartidaNode {
    Partida* partida;
    struct PartidaNode* proximo;
} PartidaNode;

struct bdpartidas {
    int nElementos;
    PartidaNode* primeiro;
    PartidaNode* ultimo;
};

// Função para criar um banco de dados de partidas
BDPartidas *criarBDPartidas() {
    BDPartidas* bd = (BDPartidas*)malloc(sizeof(BDPartidas));
    if (bd == NULL) {
        printf("Erro ao alocar memória para o banco de dados de partidas.\n");
        return NULL;
    }
    bd->nElementos = 0;
    bd->primeiro = NULL;
    bd->ultimo = NULL;

    return bd;
}


// insere uma partida no banco de dados
int adicionarPartida(BDPartidas* bd, Partida* partida) {
    PartidaNode* novoNo = (PartidaNode*)malloc(sizeof(PartidaNode));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória para o novo nó da lista de partidas.\n");
        return 0;
    }
    novoNo->partida = partida;
    novoNo->proximo = NULL;

    if (bd->primeiro == NULL) {
        bd->primeiro = novoNo;
    } else {
        bd->ultimo->proximo = novoNo;
    }
    bd->ultimo = novoNo;
    bd->nElementos++;
    return 1;
}

//cria Vetor de um arquivo externo
BDPartidas* criarBDPartidasDeArquivo(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return NULL;
    }

    BDPartidas* bd = criarBDPartidas();  // Cria um banco de dados com capacidade inicial
    if (bd == NULL) {
        fclose(arquivo);
        return NULL;
    }

    // pula cabeçalho do arquivo
    char linha[100];
    fgets(linha, sizeof(linha), arquivo);

    int id, team1, team2, golsTeam1, golsTeam2;

    // Lê as partidas do arquivo e as adiciona ao banco de dados
    while (fscanf(arquivo, " %d,%d,%d,%d,%d", &id, &team1, &team2, &golsTeam1, &golsTeam2) == 5) {
        Partida* partida = criarPartida(id, team1, team2, golsTeam1, golsTeam2);
        if (partida == NULL) {
            printf("Erro ao criar partida a partir dos dados do arquivo.\n");
            break;
        }
        int adicionado = adicionarPartida(bd, partida);
        if (adicionado == 0) {
            free(partida);
            printf("Erro ao adicionar partida ao banco de dados.\n");
            break;
        }
    }

    fclose(arquivo);
    return bd;
}

int getSizeofBDPartidas(BDPartidas* bd) {
    if (bd != NULL) {
        return bd->nElementos;
    }
    return -1;  // Valor inválido se o banco de dados for NULL
}

Partida* getPartida(BDPartidas* bd, int index) {
    if (bd != NULL && index >= 0 && index < bd->nElementos) {
        PartidaNode* atual = bd->primeiro;
        for (int i = 0; i < index; i++) {
            atual = atual->proximo;
        }
        return atual->partida;
    }
    return NULL;  // Retorna NULL se o índice for inválido ou o banco de dados for NULL
}

// Função para buscar partidas onde o team mandante tem um nome que corresponde ao prefixo fornecido
BDPartidas* buscarPartidaPorNomeTeamMandante(BDPartidas* bdPartidas, char* prefixo, BDTeams* bdTeams) {
    BDPartidas* partidasEncontradas = criarBDPartidas(); // Cria um novo banco de dados para armazenar as partidas encontradas
    BDTeams* teamsComPrefixo = buscarPorTeamNoBD(bdTeams, prefixo); // Busca os teams que correspondem ao prefixo fornecido

    for (int i = 0; i < getSizeofBDPartidas(bdPartidas); i++) {
        Partida* p = getPartida(bdPartidas, i);
        for (int j = 0; j < getSizeofBDTeams(teamsComPrefixo); j++) {
            Team* t = getTeam(teamsComPrefixo, j);
            if (getIdTeam1(p) == getIdTeam(t)) { // Verifica se o team é o mandante
                int sucesso = adicionarPartida(partidasEncontradas, p); // Adiciona a partida ao banco de dados de partidas encontradas
                if (sucesso == 0) {
                    liberarBDPartidasAux(partidasEncontradas);
                    return NULL; // Retorna NULL em caso de erro ao adicionar a partida
                }
            }
        }
    }

    liberarBDTeamsAux(teamsComPrefixo);
    return partidasEncontradas; // Retorna o banco de dados com as partidas encontradas
}

// Função para buscar partidas onde o team visitante tem um nome que corresponde ao prefixo fornecido
BDPartidas* buscarPartidaPorNomeTeamVisitante(BDPartidas* bdPartidas, char* prefixo, BDTeams* bdTeams) {
    BDPartidas* partidasEncontradas = criarBDPartidas(); // Cria um novo banco de dados para armazenar as partidas encontradas
    BDTeams* teamsComPrefixo = buscarPorTeamNoBD(bdTeams, prefixo); // Busca os teams que correspondem ao prefixo fornecido

    for (int i = 0; i < getSizeofBDPartidas(bdPartidas); i++) {
        Partida* p = getPartida(bdPartidas, i);
        for (int j = 0; j < getSizeofBDTeams(teamsComPrefixo); j++) {
            Team* t = getTeam(teamsComPrefixo, j);
            if (getIdTeam2(p) == getIdTeam(t)) { // Verifica se o team é o mandante
                int sucesso = adicionarPartida(partidasEncontradas, p); // Adiciona a partida ao banco de dados de partidas encontradas
                if (sucesso == 0) {
                    liberarBDPartidasAux(partidasEncontradas);
                    return NULL; // Retorna NULL em caso de erro ao adicionar a partida
                }
            }
        }
    }

    liberarBDTeamsAux(teamsComPrefixo);
    return partidasEncontradas; // Retorna o banco de dados com as partidas encontradas
}

// Função para liberar memória alocada para o banco de dados de partidas
void liberarBDPartidas(BDPartidas* bd) {
    if (bd != NULL) {
        PartidaNode* atual = bd->primeiro;

        while (atual != NULL) {
            PartidaNode* proximo = atual->proximo;
            liberarPartida(atual->partida);
            free(atual);
            atual = proximo;
        }

        free(bd);
    }
}

// ===================================================================

// id(identificador) da partida e não a posição dela no banco de dados(q pode mudar).
Partida* buscarPartidaPorId(BDPartidas* bd, int id) {
    if (bd == NULL) {
        return NULL;
    }

    for (int i = 0; i < getSizeofBDPartidas(bd); i++) {
        Partida* p = getPartida(bd, i);

        if (getIdPartida(p) == id) {
            return p;
        }
    }

    return NULL;
}

// Função para atualizar dados de uma partida
int atualizarPartida(BDPartidas* bd, int id, int golsTeam1, int golsTeam2) {
    if (golsTeam1 < 0 || golsTeam2 < 0) {
        return 0;
    }

    Partida* p = buscarPartidaPorId(bd, id);

    if (p == NULL) {
        return 0;
    }

    setPlacarPartida(p, golsTeam1, golsTeam2);


    return 1;
}

/// Remove uma partida pelo ID, religando os nós da lista.
// É necessário guardar o nó anterior para atualizar o encadeamento
// quando o nó removido está no meio ou no fim da lista.
int removerPartidaBD(BDPartidas* bd, int id) {
    if (bd == NULL) {
        return 0;
    }

    PartidaNode* atual = bd->primeiro;
    PartidaNode* anterior = NULL;

    while (atual != NULL && getIdPartida(atual->partida) != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        return 0;
    }

    if (anterior == NULL) {
        bd->primeiro = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    if (atual == bd->ultimo) {
        bd->ultimo = anterior;
    }

    liberarPartida(atual->partida);
    free(atual);
    bd->nElementos--;

    return 1;

}

int getIdUltimaPartida(BDPartidas* bd) {
    if (bd == NULL || bd->ultimo == NULL) {
        return -1;  // Indica que não há partidas no banco de dados
    }
    return getIdPartida(bd->ultimo->partida);
}

// Função para inserir uma partida no banco de dados
int inserirPartidaBD(BDPartidas* bd, Partida* partida) {
    if (bd == NULL || partida == NULL) {
        printf("Banco de dados inválido.\n");
        return 0;
    }
    if(partida == NULL) {
        printf("Partida inválida.\n");
        return 0;
    }

    PartidaNode* novoNode = (PartidaNode*)malloc(sizeof(PartidaNode));
    if (novoNode == NULL) {
        return 0;
    }

    novoNode->partida = partida;
    novoNode->proximo = NULL;

    if (bd->primeiro == NULL) {
        bd->primeiro = novoNode;
        bd->ultimo = novoNode;
    } else {
        bd->ultimo->proximo = novoNode;
        bd->ultimo = novoNode;
    }

    bd->nElementos++;
    return 1;
}

// ===================================================================

// Libera apenas os nós da lista auxiliar, sem liberar as partidas.
// Usada em resultados de busca, pois as partidas pertencem ao BD principal.
void liberarBDPartidasAux(BDPartidas* bd) {
    if (bd != NULL) {
        PartidaNode* atual = bd->primeiro;

        while (atual != NULL) {
            PartidaNode* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }

        free(bd);
    }
}

// Reescreve o arquivo CSV com o estado atual da lista de partidas.
// Essa estratégia simplifica a persistência após inserções, remoções
// e atualizações.
int salvarBDPartidasEmArquivo(BDPartidas* bd, const char* nomeArquivo) {
    if (bd == NULL || nomeArquivo == NULL) {
        return 0;
    }

    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        return 0;
    }

    fprintf(arquivo, "ID,Time1,Time2,GolsTime1,GolsTime2\n");

    for (int i = 0; i < getSizeofBDPartidas(bd); i++) {
        Partida* p = getPartida(bd, i);

        fprintf(arquivo, "%d,%d,%d,%d,%d\n",
            getIdPartida(p),
            getIdTeam1(p),
            getIdTeam2(p),
            getGolsTeam1(p),
            getGolsTeam2(p)
        );
    }

    fclose(arquivo);
    return 1;
}