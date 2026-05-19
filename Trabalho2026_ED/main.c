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
    // Limpa a tela usando um comando específico para o sistema operacional
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void imprimirTabelaClassificacao(BDTeams* bd) {
    printf("Tabela de Classificação:\n");
    printf("%-20s %-10s %-10s %-10s %-10s\n", "Time", "Vitórias", "Empates", "Derrotas", "Gols Marcados");
    for (int i = 0; i < getSizeofBDTeams(bd); i++) {
        Team* t = getTeam(bd, i);
        printf("%-20s %-10d %-10d %-10d %-10d\n", getNome(t), getVitorias(t), getEmpates(t), getDerrotas(t), getGolsMarcados(t));
    }
}

void carregarDadosEmTimes(BDTeams* bd, Partida* p) {
    // Atualiza a tabela de classificação com base no resultado da partida
    int idTime1 = getIdTeam(getTeam(bd, getIdTime1(p)));
    int idTime2 = getIdTeam(getTeam(bd, getIdTime2(p)));
    int golsTime1 = getGolsTime1(p);
    int golsTime2 = getGolsTime2(p);

    Team* time1 = getTeam(bd, idTime1);
    Team* time2 = getTeam(bd, idTime2);

    if (golsTime1 > golsTime2) {
        incrementarVitorias(time1);
        incrementarDerrotas(time2);
    } else if (golsTime1 < golsTime2) {
        incrementarDerrotas(time1);
        incrementarVitorias(time2);
    } else {
        incrementarEmpates(time1);
        incrementarEmpates(time2);
    }

    incrementarGolsMarcados(time1, golsTime1);
    incrementarGolsSofridos(time1, golsTime2);
    incrementarGolsMarcados(time2, golsTime2);
    incrementarGolsSofridos(time2, golsTime1);

}

void atualizarTabelaClassificacao(BDTeams* bdTeams, BDPartidas* bdPartidas) {
    for (int i = 0; i < getSizeofBDPartidas(bdPartidas); i++) {
        Partida* p = getPartida(bdPartidas, i);
        carregarDadosEmTimes(bdTeams, p);
    }
}

int main(){

    char nomeArquivoTimes[] = "BD/times.csv";
    char nomeArquivoPartidas[] = "BD/partidas_completo.csv";
    BDTeams* bdTimes = criarBDTeamsDeArquivo(nomeArquivoTimes);
    BDPartidas* bdPartidas = criarBDPartidasDeArquivo(nomeArquivoPartidas);

    atualizarTabelaClassificacao(bdTimes, bdPartidas);

    interfaceUser();

    char opcao;
    scanf(" %c", &opcao);

    while(opcao != 'Q' && opcao != 'q'){

        limparTela();

        if(opcao == '1'){

            printf("Consultar time\n");

        }else if(opcao == '2'){

            printf("Consultar partidas\n");

        }else if(opcao == '3'){

            printf("A implementar...\n");

        }else if(opcao == '4'){

            printf("A implementar...\n");

        }else if(opcao == '5'){

            printf("A implementar...\n");

        }else if(opcao == '6'){

            printf("Tabela de classificação\n");
            imprimirTabelaClassificacao(bdTimes);

        }else{

            printf("Opção inválida.\n");
        }
        
        printf("\nVoltar para o menu principal?\nS:Sim,voltar pro menu!\nN:Não, sair do programa!\n");
        char voltarMenu;
        scanf(" %c", &voltarMenu);
        if(voltarMenu == 'N' || voltarMenu == 'n'){
            break;
        }       
        interfaceUser();
        scanf(" %c", &opcao);
    }
    printf("Saindo...\n");
    liberarBDTeams(bdTimes);
    liberarBDPartidas(bdPartidas);
    return 0;
}