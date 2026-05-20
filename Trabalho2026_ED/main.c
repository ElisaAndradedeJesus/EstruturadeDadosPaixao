#include "team.h"
#include "partida.h"
#include "bdteams.h"
#include "bdpartidas.h"
#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Função para carregar os dados de todas as partidas e atualizar os dados dos times no banco de dados de times 
// só pode ser executada 1 vez a n ser que eu crie alguma forma de resertar os dados dos times.
void carregarDadosDePartidasEmTimes(BDTeams* bdTeams, BDPartidas* bdPartidas) {
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

    carregarDadosDePartidasEmTimes(bdTimes, bdPartidas);

    interfaceUser();

    char opcao;
    scanf(" %c", &opcao);

    while(opcao != 'Q' && opcao != 'q'){

        limparTela();

        if(opcao == '1'){
            consultarTeamsEncontrados(bdTimes); // Busca o times

        }else if(opcao == '2'){ 
            consultarPartida(bdPartidas, bdTimes); // Consulta as partidas no banco de dados de partidas

        }else if(opcao == '3'){

            printf("A implementar...\n");

        }else if(opcao == '4'){

            printf("A implementar...\n");

        }else if(opcao == '5'){

            printf("A implementar...\n");

        }else if(opcao == '6'){
            imprimirClassificacao(bdTimes);

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
    liberarBDTeams(bdTimes);
    liberarBDPartidas(bdPartidas);
    return 0;
}