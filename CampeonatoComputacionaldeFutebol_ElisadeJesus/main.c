#include "team.h"
#include "partida.h"
#include "bdteams.h"
#include "bdpartidas.h"
#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){

    char nomeArquivoTeams[] = "BD/bd_times.csv";
    char nomeArquivoPartidas[] = "BD/bd_partidas.csv";
    BDTeams* bdTeams = criarBDTeamsDeArquivo(nomeArquivoTeams);
    BDPartidas* bdPartidas = criarBDPartidasDeArquivo(nomeArquivoPartidas);

    carregarDadosDePartidasEmTeams(bdTeams, bdPartidas);

    interfaceUser();

    char opcao;
    scanf(" %c", &opcao);

    while(opcao != 'Q' && opcao != 'q'){

        limparTela();

        if(opcao == '1'){
            consultarTeamsEncontrados(bdTeams); // Busca o times

        }else if(opcao == '2'){ 
            consultarPartida(bdPartidas, bdTeams); // Consulta as partidas no banco de dados de partidas

        }else if(opcao == '3'){

            printf("A implementar...\n");

        }else if(opcao == '4'){

            printf("A implementar...\n");

        }else if(opcao == '5'){

            printf("A implementar...\n");

        }else if(opcao == '6'){
            imprimirClassificacao(bdTeams);

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
    printf("저는 딸기를 사랑해요!\n");
    liberarBDTeams(bdTeams);
    liberarBDPartidas(bdPartidas);
    return 0;
}