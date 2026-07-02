#include "team.h"
#include "partida.h"
#include "bdteams.h"
#include "bdpartidas.h"
#include "menu.h"
#include "classificacao.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){

    char nomeArquivoTeams[] = "BD/bd_times.csv";
    char nomeArquivoPartidas[] = "BD/bd_partidas.csv";

    BDTeams* bdTeams = criarBDTeamsDeArquivo(nomeArquivoTeams);
    BDPartidas* bdPartidas = criarBDPartidasDeArquivo(nomeArquivoPartidas);

    carregarDadosDePartidasEmTeams(bdTeams, bdPartidas);

    Classificacao* classificacao = gerarClassificacao(bdTeams);

    interfaceUser();

    char opcao;
    scanf(" %c", &opcao);

    while(opcao != 'Q' && opcao != 'q'){

        limparTela();

        if(opcao == '1'){
            consultarTeamsEncontrados(bdTeams); // Busca o teams

        }else if(opcao == '2'){ 
            consultarPartida(bdPartidas, bdTeams); // Consulta as partidas no banco de dados de partidas

        }else if(opcao == '3'){

            atualizandoPartida(bdPartidas, bdTeams);
            atualizarDadosTeam(bdTeams, bdPartidas);
            classificacao = atualizarClassificacao(classificacao, bdTeams);

        }else if(opcao == '4'){

            removendoPartida(bdPartidas, bdTeams);
            atualizarDadosTeam(bdTeams, bdPartidas);
            classificacao = atualizarClassificacao(classificacao, bdTeams);

        }else if(opcao == '5'){

            inserindoPartida(bdPartidas, bdTeams, classificacao);
            atualizarDadosTeam(bdTeams, bdPartidas);
            classificacao = atualizarClassificacao(classificacao, bdTeams);

        }else if(opcao == '6'){
            printf("Tabela de Classificação:\n");
            imprimirClassificacao(classificacao);

        }else{

            printf("Opção inválida.\n");
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        printf("\nPressione Enter para voltar ao menu...");
        getchar();

        limparTela();
        interfaceUser();
        scanf(" %c", &opcao);
    }
    
    classificacao = atualizarClassificacao(classificacao, bdTeams);

    if(salvarClassificacaoEmArquivo(classificacao, "BD/bd_classificacao.csv")){
        printf("Classificação salva com sucesso em 'BD/bd_classificacao.csv'.\n");
    }else{
        printf("Erro ao salvar classificação em 'BD/bd_classificacao.csv'.\n");
    }
    if(salvarBDPartidasEmArquivo(bdPartidas, "BD/bd_partidas.csv")){
        printf("Banco de dados de partidas salvo com sucesso em 'BD/bd_partidas.csv'.\n");
    }else{
        printf("Erro ao salvar banco de dados de partidas em 'BD/bd_partidas.csv'.\n");
    }

    liberarBDTeams(bdTeams);
    liberarBDPartidas(bdPartidas);
    liberarClassificacao(classificacao);

    return 0;
}