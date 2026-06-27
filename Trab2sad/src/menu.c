#include "team.h"
#include "partida.h"
#include "bdteams.h"
#include "bdpartidas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void interfaceUser() {
    printf(
        "Sistema de Gerenciamento de Partidas!\n"
        "1 - Consultar time\n"
        "2 - Consultar partidas\n"
        "3 - Atualizar partida\n"
        "4 - Remover partida\n"
        "5 - Inserir partida\n"
        "6 - Imprimir tabela de classificação\n"
        "Q - Sair\n"
    );
}

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

static int compararTimesParaClassificacao(const void* a, const void* b) {
    Team* timeA = *(Team**)a;
    Team* timeB = *(Team**)b;

    if (getPontosGanhos(timeA) != getPontosGanhos(timeB)) {
        return getPontosGanhos(timeB) - getPontosGanhos(timeA);
    }
    if (getVitorias(timeA) != getVitorias(timeB)) {
        return getVitorias(timeB) - getVitorias(timeA);
    }
    if (getSaldoGols(timeA) != getSaldoGols(timeB)) {
        return getSaldoGols(timeB) - getSaldoGols(timeA);
    }
    if (getGolsMarcados(timeA) != getGolsMarcados(timeB)) {
        return getGolsMarcados(timeB) - getGolsMarcados(timeA);
    }
    return getIdTeam(timeA) - getIdTeam(timeB);
}

static void imprimirCabecalhoTimes(void) {
    printf("%-5s %-20s %-5s %-5s %-5s %-5s %-5s %-5s %-5s\n",
       "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
}

static void imprimirTime(Team* t) {
    printf("%-5d %-20s %-5d %-5d %-5d %-5d %-5d %-5d %-5d\n",
        getIdTeam(t),
        getNome(t),
        getVitorias(t),
        getEmpates(t),
        getDerrotas(t),
        getGolsMarcados(t),
        getGolsSofridos(t),
        getSaldoGols(t),
        getPontosGanhos(t));
}

void imprimirClassificacao(BDTeams* bd) {
    int total = getSizeofBDTeams(bd);
    Team** ordenados = (Team**)malloc(total * sizeof(Team*));
    if (ordenados == NULL) {
        printf("Erro ao ordenar a classificação.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        ordenados[i] = getTeam(bd, i);
    }
    qsort(ordenados, total, sizeof(Team*), compararTimesParaClassificacao);

    printf("Tabela de Classificação:\n");
    imprimirCabecalhoTimes();
    for (int i = 0; i < total; i++) {
        imprimirTime(ordenados[i]);
    }

    free(ordenados);
}

static void imprimirCabecalhoPartidas(void) {
    printf("%-5s %-20s %-20s %-8s %-8s\n", "ID", "Time1", "Time2", "Placar1", "Placar2");
}

static void imprimirPartida(Partida* p, BDTeams* bdTeams) {
    Team* timeMandante = buscarTeamPorId(bdTeams, getIdTeam1(p));
    Team* timeVisitante = buscarTeamPorId(bdTeams, getIdTeam2(p));

    printf("%-5d %-20s %-20s %-8d %-8d\n",
        getIdPartida(p),
        timeMandante != NULL ? getNome(timeMandante) : "Time inexistente",
        timeVisitante != NULL ? getNome(timeVisitante) : "Time inexistente",
        getGolsTeam1(p),
        getGolsTeam2(p)
    );
}

void printarPartidasEncontradas(BDPartidas* bdPartidas, BDTeams* bdTeams) {
    for (int i = 0; i < getSizeofBDPartidas(bdPartidas); i++) {
        imprimirPartida(getPartida(bdPartidas, i), bdTeams);
    }
}

void printarTeamsEncontrados(BDTeams* bd) {
    printf("Times encontrados:\n");
    imprimirCabecalhoTimes();
    for (int i = 0; i < getSizeofBDTeams(bd); i++) {
        imprimirTime(getTeam(bd, i));
    }
}

void consultarTeamsEncontrados(BDTeams* bd) {
    printf("Digite o nome ou prefixo do time:\n");
    char prefixo[50];
    scanf(" %49[^\n]", prefixo);

    BDTeams* resultados = buscarPorTeamNoBD(bd, prefixo);
    if (getSizeofBDTeams(resultados) == 0) {
        printf("Nenhum time encontrado com o prefixo '%s'.\n", prefixo);
    } else {
        printarTeamsEncontrados(resultados);
    }
    liberarBDTeamsAux(resultados);
}

static void imprimirResultadoBuscaPartidas(BDPartidas* partidasEncontradas, BDTeams* bdTeams, const char* mensagemVazia) {
    if (partidasEncontradas == NULL) {
        printf("Erro ao buscar partidas.\n");
        return;
    }

    if (getSizeofBDPartidas(partidasEncontradas) == 0) {
        printf("%s\n", mensagemVazia);
    } else {
        printf("Partidas encontradas:\n");
        imprimirCabecalhoPartidas();
        printarPartidasEncontradas(partidasEncontradas, bdTeams);
    }
}

void consultarPartida(BDPartidas* bdPartidas, BDTeams* bdTeams) {
    printf(
        "Escolha o modo de consulta:\n"
        "1 - Por time mandante\n"
        "2 - Por time visitante\n"
        "3 - Por time mandante ou visitante\n"
        "4 - Retornar ao menu principal\n"
    );

    char opcao;
    scanf(" %c", &opcao);

    if (opcao == '4') {
        return;
    }

    if (opcao != '1' && opcao != '2' && opcao != '3') {
        printf("Opção inválida.\n");
        return;
    }

    char prefixo[50];
    printf("Digite o nome ou prefixo do time:\n");
    scanf(" %49[^\n]", prefixo);

    if (opcao == '1') {
        BDPartidas* encontradas = buscarPartidaPorNomeTeamMandante(bdPartidas, prefixo, bdTeams);
        imprimirResultadoBuscaPartidas(encontradas, bdTeams, "Nenhuma partida encontrada para o time mandante.");
        liberarBDPartidasAux(encontradas);
    } else if (opcao == '2') {
        BDPartidas* encontradas = buscarPartidaPorNomeTeamVisitante(bdPartidas, prefixo, bdTeams);
        imprimirResultadoBuscaPartidas(encontradas, bdTeams, "Nenhuma partida encontrada para o time visitante.");
        liberarBDPartidasAux(encontradas);
    } else {
        BDPartidas* mandante = buscarPartidaPorNomeTeamMandante(bdPartidas, prefixo, bdTeams);
        BDPartidas* visitante = buscarPartidaPorNomeTeamVisitante(bdPartidas, prefixo, bdTeams);

        int totalMandante = mandante != NULL ? getSizeofBDPartidas(mandante) : 0;
        int totalVisitante = visitante != NULL ? getSizeofBDPartidas(visitante) : 0;

        if (totalMandante == 0 && totalVisitante == 0) {
            printf("Nenhuma partida encontrada para o time mandante ou visitante.\n");
        } else {
            printf("Partidas encontradas:\n");
            imprimirCabecalhoPartidas();
            if (mandante != NULL) {
                printarPartidasEncontradas(mandante, bdTeams);
            }
            if (visitante != NULL) {
                printarPartidasEncontradas(visitante, bdTeams);
            }
        }

        liberarBDPartidasAux(mandante);
        liberarBDPartidasAux(visitante);
    }
}

static int salvarAlteracoes(BDPartidas* bdPartidas, BDTeams* bdTeams, const char* arquivoPartidas, const char* arquivoClassificacao) {
    carregarDadosDePartidasEmTeams(bdTeams, bdPartidas);
    return salvarBDPartidasEmArquivo(bdPartidas, arquivoPartidas)
        && salvarClassificacaoEmArquivo(bdTeams, arquivoClassificacao);
}

static int confirmarOperacao(void) {
    char confirmacao;
    scanf(" %c", &confirmacao);
    return confirmacao == 'S' || confirmacao == 's';
}

void atualizarPartidaMenu(BDPartidas* bdPartidas, BDTeams* bdTeams, const char* arquivoPartidas, const char* arquivoClassificacao) {
    consultarPartida(bdPartidas, bdTeams);

    int id;
    printf("Digite o ID do registro a ser atualizado:\n");
    if (scanf(" %d", &id) != 1) {
        printf("ID inválido.\n");
        return;
    }

    Partida* partida = buscarPartidaPorId(bdPartidas, id);
    if (partida == NULL) {
        printf("Partida não encontrada.\n");
        return;
    }

    char entradaGols1[16];
    char entradaGols2[16];
    int novosGols1 = getGolsTeam1(partida);
    int novosGols2 = getGolsTeam2(partida);

    printf("Digite o novo valor para Placar1 e Placar2 (use '-' para manter):\n");
    scanf(" %15s %15s", entradaGols1, entradaGols2);

    if (strcmp(entradaGols1, "-") != 0) {
        novosGols1 = atoi(entradaGols1);
    }
    if (strcmp(entradaGols2, "-") != 0) {
        novosGols2 = atoi(entradaGols2);
    }

    if (novosGols1 < 0 || novosGols2 < 0) {
        printf("Os placares não podem ser negativos.\n");
        return;
    }

    printf("Confirma os novos valores para o registro abaixo? (S/N)\n");
    imprimirCabecalhoPartidas();
    printf("%-5d %-20s %-20s %-8d %-8d\n",
        getIdPartida(partida),
        getNome(buscarTeamPorId(bdTeams, getIdTeam1(partida))),
        getNome(buscarTeamPorId(bdTeams, getIdTeam2(partida))),
        novosGols1,
        novosGols2);

    if (!confirmarOperacao()) {
        printf("Atualização cancelada.\n");
        return;
    }

    if (atualizarPlacarPartida(bdPartidas, id, novosGols1, novosGols2)
        && salvarAlteracoes(bdPartidas, bdTeams, arquivoPartidas, arquivoClassificacao)) {
        printf("Registro atualizado com sucesso.\n");
    } else {
        printf("Erro ao atualizar o registro.\n");
    }
}

void removerPartidaMenu(BDPartidas* bdPartidas, BDTeams* bdTeams, const char* arquivoPartidas, const char* arquivoClassificacao) {
    consultarPartida(bdPartidas, bdTeams);

    int id;
    printf("Digite o ID do registro a ser removido:\n");
    if (scanf(" %d", &id) != 1) {
        printf("ID inválido.\n");
        return;
    }

    Partida* partida = buscarPartidaPorId(bdPartidas, id);
    if (partida == NULL) {
        printf("Partida não encontrada.\n");
        return;
    }

    printf("Tem certeza de que deseja excluir o registro abaixo? (S/N)\n");
    imprimirCabecalhoPartidas();
    imprimirPartida(partida, bdTeams);

    if (!confirmarOperacao()) {
        printf("Remoção cancelada.\n");
        return;
    }

    if (removerPartidaPorId(bdPartidas, id)
        && salvarAlteracoes(bdPartidas, bdTeams, arquivoPartidas, arquivoClassificacao)) {
        printf("Registro removido com sucesso.\n");
    } else {
        printf("Erro ao remover o registro.\n");
    }
}

void inserirPartidaMenu(BDPartidas* bdPartidas, BDTeams* bdTeams, const char* arquivoPartidas, const char* arquivoClassificacao) {
    int idTime1, idTime2, golsTime1, golsTime2;

    printf("Para inserir um novo registro, digite Time1, Time2, Placar1 e Placar2:\n");
    if (scanf(" %d %d %d %d", &idTime1, &idTime2, &golsTime1, &golsTime2) != 4) {
        printf("Dados inválidos.\n");
        return;
    }

    Team* time1 = buscarTeamPorId(bdTeams, idTime1);
    Team* time2 = buscarTeamPorId(bdTeams, idTime2);
    if (time1 == NULL || time2 == NULL) {
        printf("Um dos times informados não existe.\n");
        return;
    }
    if (idTime1 == idTime2) {
        printf("Uma partida precisa ter dois times diferentes.\n");
        return;
    }
    if (golsTime1 < 0 || golsTime2 < 0) {
        printf("Os placares não podem ser negativos.\n");
        return;
    }

    int id = gerarProximoIdPartida(bdPartidas);
    printf("Confirma a inserção do registro abaixo? (S/N)\n");
    imprimirCabecalhoPartidas();
    printf("%-5d %-20s %-20s %-8d %-8d\n",
        id,
        getNome(time1),
        getNome(time2),
        golsTime1,
        golsTime2);

    if (!confirmarOperacao()) {
        printf("Inserção cancelada.\n");
        return;
    }

    Partida* novaPartida = criarPartida(id, idTime1, idTime2, golsTime1, golsTime2);
    if (!adicionarPartida(bdPartidas, novaPartida)) {
        liberarPartida(novaPartida);
        printf("Erro ao inserir o registro.\n");
        return;
    }

    if (salvarAlteracoes(bdPartidas, bdTeams, arquivoPartidas, arquivoClassificacao)) {
        printf("O registro foi inserido com sucesso.\n");
    } else {
        printf("Registro inserido em memória, mas houve erro ao salvar os arquivos.\n");
    }
}
