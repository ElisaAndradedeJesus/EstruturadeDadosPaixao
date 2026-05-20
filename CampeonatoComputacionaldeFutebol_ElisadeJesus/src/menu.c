#include "team.h"
#include "partida.h"
#include "bdteams.h"
#include "bdpartidas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Conjunto de printes pra fazer a telinha inicial do programa
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

// Função para limpar a tela. Pra evitar que o menu fique poluído com as informações das consultas e atualizações
void limparTela() {
    // Limpa a tela usando um comando específico para o sistema operacional
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Função para imprimir a tabela de classificação dos times
void imprimirClassificacao(BDTeams* bd) {
    printf("Tabela de Classificação:\n");
    printf("%-5s %-20s %-5s %-5s %-5s %-5s %-5s %-5s %-5s\n",
       "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");

    for (int i = 0; i < getSizeofBDTeams(bd); i++) {
        Team* t = getTeam(bd, i);
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
}

// Função para imprimir as partidas encontradas, mostrando o nome dos times e o resultado da partida
void printarPartidasEncontradas(BDPartidas* bdPartidas, BDTeams* bdTeams) {
    for (int i = 0; i < getSizeofBDPartidas(bdPartidas); i++) {
        Partida* p = getPartida(bdPartidas, i);
        Team* timeMandante = buscarTeamPorId(bdTeams, getIdTime1(p));
        Team* timeVisitante = buscarTeamPorId(bdTeams, getIdTime2(p));
        printf("%-5d %-20s %d x %d %-20s\n",
            getIdPartida(p),
            getNome(timeMandante),
            getGolsTime1(p),
            getGolsTime2(p),
            getNome(timeVisitante)
        );
    }
    
}

// Função para imprimir os times encontrados, mostrando o nome do time e suas estatísticas
// )Função auxiliar de consultarTeamsEncontrados, que é a função principal para consultar times encontrados, mostrando o nome do time e suas estatísticas)
void printarTimesEncontrados(BDTeams* bd) {
    printf("Times encontrados:\n");
    printf("%-5s %-20s %-5s %-5s %-5s %-5s %-5s %-5s %-5s\n",
       "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
    for (int i = 0; i < getSizeofBDTeams(bd); i++) {
        Team* t = getTeam(bd, i);
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
}

// Função para consultar times encontrados, mostrando o nome do time e suas estatísticas
void consultarTeamsEncontrados(BDTeams* bd) {
    //Lê o nome ou prefixo do time a ser consultado
    printf("Digite o nome ou prefixo do time:\n");
    char prefixo[50];

    scanf(" %49[^\n]", prefixo);

    BDTeams* resultados = buscarPorTeamNoBD(bd, prefixo);
    if (getSizeofBDTeams(resultados) == 0) {
        printf("Nenhum time encontrado com o prefixo '%s'.\n", prefixo);
    } else {
        printarTimesEncontrados(resultados);
    }
    liberarBDTeamsAux(resultados);
}

// Função para consultar partidas 
void consultarPartida(BDPartidas* bdPartidas,BDTeams* bdTeams) {
    printf(
        "Escolha o modo de consulta:\n"
        "1 - Por time mandante\n"
        "2 - Por time visitante\n"
        "3 - Por time mandante ou visitante\n"
        "4 - Retornar ao menu principal\n"
    );

    char opcao;
    scanf(" %c", &opcao);

    if(opcao == '1'){
        char prefixo[50];
        printf("Digite o nome ou prefixo do time mandante:\n");
        scanf(" %49[^\n]", prefixo);

        printf("Partidas encontradas:\n");
        printf("%-5s %-20s %-20s\n", "ID", "Time1", "Time2");

        BDPartidas* partidasEncontradas = buscarPartidaPorNomeTimeMandante(bdPartidas, prefixo, bdTeams);
        if(partidasEncontradas == NULL){
            printf("Erro ao buscar partidas para o time mandante com o prefixo '%s'.\n", prefixo);
        } else{
            if (getSizeofBDPartidas(partidasEncontradas) == 0) {
                printf("Nenhuma partida encontrada com o critério de busca fornecido para o time mandante.\n");
            } else{
                printarPartidasEncontradas(partidasEncontradas, bdTeams);
            }
        }
        liberarBDPartidasAux(partidasEncontradas);
    }else if(opcao == '2'){
        char prefixo[50];
        printf("Digite o nome ou prefixo do time visitante:\n");
        scanf(" %49[^\n]", prefixo);

        printf("Partidas encontradas:\n");
        printf("%-5s %-20s %-20s\n", "ID", "Time1", "Time2");

        BDPartidas* partidasEncontradas = buscarPartidaPorNomeTimeVisitante(bdPartidas, prefixo, bdTeams);
        if (partidasEncontradas == NULL) {
            printf("Erro ao buscar partidas para o time visitante com o prefixo '%s'.\n", prefixo);
        } else {    
            if (getSizeofBDPartidas(partidasEncontradas) == 0) {
                printf("Nenhuma partida encontrada com o critério de busca fornecido para o time visitante.\n");
            } else {
                printarPartidasEncontradas(partidasEncontradas, bdTeams);
            }
        }
        liberarBDPartidasAux(partidasEncontradas);
    }else if(opcao == '3'){ 
        char prefixo[50];
        printf("Digite o nome ou prefixo do time mandante:\n");
        scanf(" %49[^\n]", prefixo);

        printf("Partidas encontradas:\n");
        printf("%-5s %-20s %-20s\n", "ID", "Time1", "Time2");

        BDPartidas* partidasEncontradasMandante = buscarPartidaPorNomeTimeMandante(bdPartidas, prefixo, bdTeams);
        BDPartidas* partidasEncontradasVisitante = buscarPartidaPorNomeTimeVisitante(bdPartidas, prefixo, bdTeams);

        if(partidasEncontradasMandante == NULL && partidasEncontradasVisitante == NULL){
            printf("Erro ao buscar partidas para o time com o prefixo '%s'.\n", prefixo);
        } else if(getSizeofBDPartidas(partidasEncontradasMandante) == 0 && getSizeofBDPartidas(partidasEncontradasVisitante) == 0){
             printf("Nenhuma partida encontrada com o critério de busca fornecido para o time mandante ou visitante.\n");
        } else {
             printarPartidasEncontradas(partidasEncontradasMandante, bdTeams);
             printarPartidasEncontradas(partidasEncontradasVisitante, bdTeams);
        }
        if (getSizeofBDPartidas(partidasEncontradasMandante) == 0 && getSizeofBDPartidas(partidasEncontradasVisitante) == 0)
            printf("Nenhuma partida encontrada com o critério de busca fornecido para o time mandante ou visitante.\n");
            
        else{
            printarPartidasEncontradas(partidasEncontradasMandante, bdTeams);
            printarPartidasEncontradas(partidasEncontradasVisitante, bdTeams);
        }

        liberarBDPartidasAux(partidasEncontradasMandante);
        liberarBDPartidasAux(partidasEncontradasVisitante);
    }else if(opcao == '4'){

        printf("Saindo... \n");
    } else{
        printf("Opção inválida! Digite uma opção válida:\n");
        scanf(" %c", &opcao);
    }

}