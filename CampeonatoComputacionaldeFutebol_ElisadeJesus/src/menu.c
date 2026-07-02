#include "team.h"
#include "partida.h"
#include "bdteams.h"
#include "bdpartidas.h"
#include "classificacao.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Conjunto de printes pra fazer a telinha inicial do programa
void interfaceUser() {
    printf(
        "Sistema de Gerenciamento de Partidas!\n"
        "1 - Consultar team\n"
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


// Função para imprimir as partidas encontradas, mostrando o nome dos teams e o resultado da partida
void printarPartidasEncontradas(BDPartidas* bdPartidas, BDTeams* bdTeams) {
    for (int i = 0; i < getSizeofBDPartidas(bdPartidas); i++) {
        Partida* p = getPartida(bdPartidas, i);
        Team* teamMandante = buscarTeamPorId(bdTeams, getIdTeam1(p));
        Team* teamVisitante = buscarTeamPorId(bdTeams, getIdTeam2(p));
        printf("%-5d %-20s %-20s %-8d %-8d\n",
            getIdPartida(p),
            getNome(teamMandante),
            getNome(teamVisitante),
            getGolsTeam1(p),
            getGolsTeam2(p)
        );
    }
    
}

// Função para imprimir os teams encontrados, mostrando o nome do team e suas estatísticas
// Função auxiliar de consultarTeamsEncontrados, que é a função principal para consultar teams encontrados, mostrando o nome do team e suas estatísticas
void printarTeamsEncontrados(BDTeams* bd) {
    printf("Teams encontrados:\n");
    printf("%-5s %-20s %-5s %-5s %-5s %-5s %-5s %-5s %-5s\n",
       "ID", "Team", "V", "E", "D", "GM", "GS", "S", "PG");
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

// Função para consultar teams encontrados, mostrando o nome do team e suas estatísticas
void consultarTeamsEncontrados(BDTeams* bd) {
    //Lê o nome ou prefixo do team a ser consultado
    printf("Digite o nome ou prefixo do team:\n");
    char prefixo[50];

    scanf(" %49[^\n]", prefixo);

    BDTeams* resultados = buscarPorTeamNoBD(bd, prefixo);
    if (getSizeofBDTeams(resultados) == 0) {
        printf("Nenhum team encontrado com o prefixo '%s'.\n", prefixo);
    } else {
        printarTeamsEncontrados(resultados);
    }
    liberarBDTeamsAux(resultados);
}

// Função para consultar partidas 
void consultarPartida(BDPartidas* bdPartidas,BDTeams* bdTeams) {
    printf(
        "Escolha o modo de consulta:\n"
        "1 - Por team mandante\n"
        "2 - Por team visitante\n"
        "3 - Por team mandante ou visitante\n"
        "4 - Retornar ao menu principal\n"
    );

    char opcao;
    scanf(" %c", &opcao);

    if(opcao == '1'){
        char prefixo[50];
        printf("Digite o nome ou prefixo do team mandante:\n");
        scanf(" %49[^\n]", prefixo);

        printf("Partidas encontradas:\n");
        printf("%-5s %-20s %-20s %-8s %-8s\n", "ID", "Team1", "Team2", "Placar1", "Placar2");

        BDPartidas* partidasEncontradas = buscarPartidaPorNomeTeamMandante(bdPartidas, prefixo, bdTeams);
        if(partidasEncontradas == NULL){
            printf("Erro ao buscar partidas para o team mandante com o prefixo '%s'.\n", prefixo);
        } else{
            if (getSizeofBDPartidas(partidasEncontradas) == 0) {
                printf("Nenhuma partida encontrada com o critério de busca fornecido para o team mandante.\n");
            } else{
                printarPartidasEncontradas(partidasEncontradas, bdTeams);
            }
        }
        liberarBDPartidasAux(partidasEncontradas);
    }else if(opcao == '2'){
        char prefixo[50];
        printf("Digite o nome ou prefixo do team visitante:\n");
        scanf(" %49[^\n]", prefixo);

        printf("Partidas encontradas:\n");
        printf("%-5s %-20s %-20s %-8s %-8s\n", "ID", "Team1", "Team2", "Placar1", "Placar2");

        BDPartidas* partidasEncontradas = buscarPartidaPorNomeTeamVisitante(bdPartidas, prefixo, bdTeams);
        if (partidasEncontradas == NULL) {
            printf("Erro ao buscar partidas para o team visitante com o prefixo '%s'.\n", prefixo);
        } else {    
            if (getSizeofBDPartidas(partidasEncontradas) == 0) {
                printf("Nenhuma partida encontrada com o critério de busca fornecido para o team visitante.\n");
            } else {
                printarPartidasEncontradas(partidasEncontradas, bdTeams);
            }
        }
        liberarBDPartidasAux(partidasEncontradas);
    }else if(opcao == '3'){ 
        char prefixo[50];
        printf("Digite o nome ou prefixo do team mandante:\n");
        scanf(" %49[^\n]", prefixo);

        printf("Partidas encontradas:\n");
        printf("%-5s %-20s %-20s %-8s %-8s\n", "ID", "Team1", "Team2", "Placar1", "Placar2");

        BDPartidas* partidasEncontradasMandante = buscarPartidaPorNomeTeamMandante(bdPartidas, prefixo, bdTeams);
        BDPartidas* partidasEncontradasVisitante = buscarPartidaPorNomeTeamVisitante(bdPartidas, prefixo, bdTeams);

        if(partidasEncontradasMandante == NULL && partidasEncontradasVisitante == NULL){
            printf("Erro ao buscar partidas para o team com o prefixo '%s'.\n", prefixo);
        } else if(getSizeofBDPartidas(partidasEncontradasMandante) == 0 && getSizeofBDPartidas(partidasEncontradasVisitante) == 0){
             printf("Nenhuma partida encontrada com o critério de busca fornecido para o team mandante ou visitante.\n");
        } else {
             printarPartidasEncontradas(partidasEncontradasMandante, bdTeams);
             printarPartidasEncontradas(partidasEncontradasVisitante, bdTeams);
        }
        if (getSizeofBDPartidas(partidasEncontradasMandante) == 0 && getSizeofBDPartidas(partidasEncontradasVisitante) == 0)
            printf("Nenhuma partida encontrada com o critério de busca fornecido para o team mandante ou visitante.\n");
            
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

// Fluxo de atualização: consulta a partida, lê os novos placares,
// exibe uma prévia e só altera o BD após confirmação do usuário.

void atualizandoPartida(BDPartidas* bdPartidas, BDTeams* bdTeams) {

    // Verifica se os bancos necessários foram carregados corretamente.    
    if (bdPartidas == NULL) {
        printf("Banco de dados de partidas inválido.\n");
        return;
    }
    if (bdTeams == NULL) {
        printf("Banco de dados de teams inválido.\n");
        return;
    }
    // Mostra a consulta de partidas antes da alteração, pois o enunciado pede
    // que o usuário localize o registro antes de informar o ID.
    consultarPartida(bdPartidas, bdTeams);

    int id;
    printf("Digite o ID da partida a ser atualizada:\n");
    scanf("%d", &id);

    // Busca a partida pelo ID informado. Se não existir, a atualização é cancelada.
    Partida* partida = buscarPartidaPorId(bdPartidas, id);

    if (partida == NULL) {
    printf("Partida não encontrada.\n");
    return;
    }

    // Começa com o placar atual da partida.    
    // Assim, se o usuário digitar "-", o campo continua com o valor antigo.
    int golsTeam1 = getGolsTeam1(partida);
    int golsTeam2 = getGolsTeam2(partida);

    printf("Digite o novo valor para os campos Placar1 e Placar2 (para manter o valor atual de um campo, digite ’-’):\n");
    char placar1[20], placar2[20];

    // Lê os dois campos como texto porque o usuário pode digitar número ou "-".
    scanf(" %19s", placar1);
    scanf(" %19s", placar2);

    // Se o usuário digitou um número, substitui o valor antigo.
    // Se digitou "-", mantém o valor que já estava em golsTeam1/golsTeam2.
    if (strcmp(placar1, "-") != 0) {
        golsTeam1 = atoi(placar1);
    }
    if (strcmp(placar2, "-") != 0) {
        golsTeam2 = atoi(placar2);
    }

    printf("Confirma os novos valores para o registro abaixo? (S/N)\n");
    printf("%-5s %-20s %-20s %-8s %-8s\n", "ID", "Team1", "Team2", "Placar1", "Placar2");

    // Recupera os nomes dos teams para imprimir uma confirmação mais legível.
    Team* team1 = buscarTeamPorId(bdTeams, getIdTeam1(partida));
    Team* team2 = buscarTeamPorId(bdTeams, getIdTeam2(partida));

    printf("%-5d %-20s %-20s %-8d %-8d\n",
           getIdPartida(partida),
           getNome(team1),
           getNome(team2),
           golsTeam1,
           golsTeam2
    );
    char resposta;
    scanf(" %c", &resposta);

    // Só aplica a alteração depois que o usuário confirma a prévia.
    if (resposta == 'S' || resposta == 's') {
        int sucesso = atualizarPartida(bdPartidas, id, golsTeam1, golsTeam2);
        if (sucesso) {
            printf("Registro atualizado com sucesso.\n");
            
        } else {
            printf("Erro ao atualizar o placar. Verifique se o ID da partida está correto e se os gols são válidos.\n");
        }

    }

    
}

// Fluxo de remoção: consulta a partida, mostra o registro escolhido
// e remove do BD apenas após confirmação do usuário.
void removendoPartida(BDPartidas* bdPartidas, BDTeams* bdTeams){

    // Verifica se os bancos necessários foram carregados corretamente.  
    if (bdPartidas == NULL) {
        printf("Banco de dados de partidas inválido.\n");
        return;
    }
    if (bdTeams == NULL) {
        printf("Banco de dados de teams inválido.\n");
        return;
    }

    // Consulta primeiro para evitar que o usuário precise saber o ID de memória.
    consultarPartida(bdPartidas, bdTeams);

    int id;
    printf("Digite o ID da partida a ser removida:\n");
    scanf(" %d", &id);

    // Busca a partida que será removida. Sem um ID válido, não há confirmação.
    Partida* partida = buscarPartidaPorId(bdPartidas, id);

    if (partida == NULL) {
    printf("Partida não encontrada.\n");
    return;
}

    printf("Tem certeza de que deseja excluir o registro abaixo? (S/N)\n");
    Team* team1 = buscarTeamPorId(bdTeams, getIdTeam1(partida));
    Team* team2 = buscarTeamPorId(bdTeams, getIdTeam2(partida));
    if (partida != NULL) {
        printf("%-5s %-20s %-20s %-8s %-8s\n", "ID", "Team1", "Team2", "Placar1", "Placar2");
        printf("%-5d %-20s %-20s %-8d %-8d\n",
               getIdPartida(partida),
               getNome(team1),
               getNome(team2),
               getGolsTeam1(partida),
               getGolsTeam2(partida)
        );
    }

    char resposta;
    scanf(" %c", &resposta);
    if (resposta == 'S' || resposta == 's') {
        int sucesso = removerPartidaBD(bdPartidas, id);
        if (sucesso) {
            printf("Registro removido com sucesso.\n");
        } else {
            printf("Erro ao remover a partida. Verifique se o ID da partida está correto.\n");
        }
    }
}

// Fluxo de inserção: valida se os teams existem, impede partida
// de um team contra ele mesmo e confirma os dados antes de inserir.
void inserindoPartida(BDPartidas* bdPartidas, BDTeams* bdTeams, Classificacao* classificacao) {

    // Verifica se os bancos necessários foram carregados corretamente.
    if (bdPartidas == NULL) {
        printf("Banco de dados de partidas inválido.\n");
        return;
    }
    if (bdTeams == NULL) {
        printf("Banco de dados de teams inválido.\n");
        return;
    }
    if (classificacao == NULL) {
        printf("Classificação não disponível.\n");
        return;
    }
    // Apresentando times Cadastrados:
    printf("Times Cadastrados:\n");
    imprimirClassificacao(classificacao);

    int idTeam1, idTeam2, golsTeam1, golsTeam2;

    printf("Digite os dados da nova partida:\n");
    printf("Team 1: ");
    scanf("%d", &idTeam1);

    // Como a Partida guarda apenas o ID dos teams, verificamos no BDTeams
    // se os IDs digitados realmente correspondem a teams cadastrados.
    Team* team1 = buscarTeamPorId(bdTeams, idTeam1);

    if (team1 == NULL) {
        printf("Time 1 não encontrado.\n");
        return;
    }

    printf("Team 2: ");
    scanf("%d", &idTeam2);
    Team* team2 = buscarTeamPorId(bdTeams, idTeam2);

    if (team2 == NULL) {
        printf("Time 2 não encontrado.\n");
        return;
    }

    // Uma partida não pode ter o mesmo team nos dois lados.
    if (idTeam1 == idTeam2) {
        printf("Os times não podem ser iguais.\n");
        return;
    }

    printf("Gols Time 1: ");
    scanf("%d", &golsTeam1);
    printf("Gols Time 2: ");
    scanf("%d", &golsTeam2);

    // Placares negativos não fazem sentido.
    if(golsTeam1 < 0 || golsTeam2 < 0) {
        printf("Número de gols inválido. Os gols devem ser não negativos.\n");
        return;
    }
    
    // Usa o último ID conhecido para criar um novo identificador.
    int ultimoID = getIdUltimaPartida(bdPartidas);

    // Mostra a partida antes de inserir para o usuário confirmar os dados digitados.
    printf("Tem certeza de que deseja incluir o registro abaixo? (S/N)\n");

    printf("%-5s %-20s %-20s %-8s %-8s\n", "ID", "Team1", "Team2", "Placar1", "Placar2");
    printf("%-5d %-20s %-20s %-8d %-8d\n",
        ultimoID + 1,
        getNome(team1),
        getNome(team2),
        golsTeam1,
        golsTeam2
    );

    char resposta;
    scanf(" %c", &resposta);
    if(resposta == 'N' || resposta == 'n') {
        return;
    }

    // Cria a partida
    Partida* novaPartida = criarPartida(ultimoID + 1, idTeam1, idTeam2, golsTeam1, golsTeam2);
    if (novaPartida == NULL) {
        printf("Erro ao criar nova partida.\n");
        return;
    }

    int sucesso = inserirPartidaBD(bdPartidas, novaPartida);
    if (sucesso) {
        printf("Partida inserida com sucesso.\n");
    } else {
        printf("Erro ao inserir partida.\n");
        liberarPartida(novaPartida);
    }
}