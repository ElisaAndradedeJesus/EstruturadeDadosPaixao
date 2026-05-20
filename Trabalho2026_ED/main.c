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
// Função para buscar um time pelo ID no banco de dados de times
// É uma função auxiliar para facilitar a atualização dos dados dos times com base nas partidas
Team* buscarTeamPorId(BDTeams* bd, int id) {
    for (int i = 0; i < getSizeofBDTeams(bd); i++) {
        Team* t = getTeam(bd, i);
        if (getIdTeam(t) == id) {
            return t;
        }
    }
    return NULL; // Retorna NULL se o time não for encontrado
}

//Pega os Dados de uma partida e atualiza os dados dos times envolvidos na partida, como vitórias, empates, derrotas, gols marcados e gols sofridos
// Função auxiliar de carregarDadosDePartidasEmTimes, que é a função principal para carregar os dados de todas as partidas e atualizar os dados dos times no banco de dados de times
void carregarDadosEmTimes(BDTeams* bd, Partida* p) {
    // Atualiza a tabela de classificação com base no resultado da partida
    int idTime1 = getIdTime1(p);
    int idTime2 = getIdTime2(p);
    int golsTime1 = getGolsTime1(p);
    int golsTime2 = getGolsTime2(p);

    Team* time1 = buscarTeamPorId(bd, idTime1);
    Team* time2 = buscarTeamPorId(bd, idTime2);

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

// Função para carregar os dados de todas as partidas e atualizar os dados dos times no banco de dados de times 
// só pode ser executada 1 vez a n ser que eu crie alguma forma de resertar os dados dos times.
void carregarDadosDePartidasEmTimes(BDTeams* bdTeams, BDPartidas* bdPartidas) {
    for (int i = 0; i < getSizeofBDPartidas(bdPartidas); i++) {
        Partida* p = getPartida(bdPartidas, i);
        carregarDadosEmTimes(bdTeams, p);
    }
}


BDTeams* buscarPorTeamNoBD(BDTeams* bd, char* prefixo) {
    BDTeams* resultados = criarBDTeams(); // Cria um novo banco de dados para armazenar os resultados
    for (int i = 0; i < getSizeofBDTeams(bd); i++) {
        Team* t = getTeam(bd, i);
        if (strncmp(getNome(t), prefixo, strlen(prefixo)) == 0) { // Verifica se o nome do time contém o prefixo fornecido
            adicionarTeam(resultados, t); // Adiciona o time ao banco de dados de resultados
        }
    }
    return resultados;
}

void consultarTeamsEncontrados(BDTeams* bd) {
    //Lê o nome ou prefixo do time a ser consultado
    printf("Digite o nome ou prefixo do time:\n");
    char prefixo[50];

    scanf(" %49[^\n]", prefixo);
    
    printf("Times encontrados com o prefixo '%s':\n", prefixo);
    printf("%-5s %-20s %-5s %-5s %-5s %-5s %-5s %-5s %-5s\n",
       "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");

    BDTeams* resultados = buscarPorTeamNoBD(bd, prefixo);
    if (getSizeofBDTeams(resultados) == 0) {
        printf("Nenhum time encontrado com o prefixo '%s'.\n", prefixo);
    } else {
        for (int i = 0; i < getSizeofBDTeams(resultados); i++) {
        Team* t = getTeam(resultados, i);
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
    liberarBDTeamsAux(resultados);
}

// Função para buscar partidas onde o time mandante tem um nome que corresponde ao prefixo fornecido
BDPartidas* buscarPartidaPorNomeTimeMandante(BDPartidas* bdPartidas, char* prefixo, BDTeams* bdTeams) {
    BDPartidas* partidasEncontradas = criarBDPartidas(); // Cria um novo banco de dados para armazenar as partidas encontradas
    BDTeams* timesComPrefixo = buscarPorTeamNoBD(bdTeams, prefixo); // Busca os times que correspondem ao prefixo fornecido

    for (int i = 0; i < getSizeofBDPartidas(bdPartidas); i++) {
        Partida* p = getPartida(bdPartidas, i);
        for (int j = 0; j < getSizeofBDTeams(timesComPrefixo); j++) {
            Team* t = getTeam(timesComPrefixo, j);
            if (getIdTime1(p) == getIdTeam(t)) { // Verifica se o time é o mandante
                int sucesso = adicionarPartida(partidasEncontradas, p); // Adiciona a partida ao banco de dados de partidas encontradas
                if (sucesso == 0) {
                    liberarBDPartidasAux(partidasEncontradas);
                    return NULL; // Retorna NULL em caso de erro ao adicionar a partida
                }
            }
        }
    }

    liberarBDTeamsAux(timesComPrefixo);
    return partidasEncontradas; // Retorna o banco de dados com as partidas encontradas
}

// Função para buscar partidas onde o time visitante tem um nome que corresponde ao prefixo fornecido
BDPartidas* buscarPartidaPorNomeTimeVisitante(BDPartidas* bdPartidas, char* prefixo, BDTeams* bdTeams) {
    BDPartidas* partidasEncontradas = criarBDPartidas(); // Cria um novo banco de dados para armazenar as partidas encontradas
    BDTeams* timesComPrefixo = buscarPorTeamNoBD(bdTeams, prefixo); // Busca os times que correspondem ao prefixo fornecido

    for (int i = 0; i < getSizeofBDPartidas(bdPartidas); i++) {
        Partida* p = getPartida(bdPartidas, i);
        for (int j = 0; j < getSizeofBDTeams(timesComPrefixo); j++) {
            Team* t = getTeam(timesComPrefixo, j);
            if (getIdTime2(p) == getIdTeam(t)) { // Verifica se o time é o mandante
                int sucesso = adicionarPartida(partidasEncontradas, p); // Adiciona a partida ao banco de dados de partidas encontradas
                if (sucesso == 0) {
                    liberarBDPartidasAux(partidasEncontradas);
                    return NULL; // Retorna NULL em caso de erro ao adicionar a partida
                }
            }
        }
    }

    liberarBDTeamsAux(timesComPrefixo);
    return partidasEncontradas; // Retorna o banco de dados com as partidas encontradas
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
        
        printf("\nVoltar para o menu principal?\nS:Sim,voltar pro menu!\nN:Não, sair do programa!\n");

        char voltarMenu;
        scanf(" %c", &voltarMenu);
        
        if(voltarMenu == 'N' || voltarMenu == 'n'){
            break;
        }       
        limparTela();
        interfaceUser();
        scanf(" %c", &opcao);
    }
    printf("저는 딸기를 사랑해요!\n");
    liberarBDTeams(bdTimes);
    liberarBDPartidas(bdPartidas);
    return 0;
}