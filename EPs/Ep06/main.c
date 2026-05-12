#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    char nome[50];
    int pontos;
} Time;

Time* criarTime(){
    Time *novoTime = (Time*)malloc(sizeof(Time));
    return novoTime;
}
void lerDadosTime(Time *time){

    printf("Criando novo time!\n");
    printf("ID: ");
    scanf(" %d", &time->id);
    printf("Nome: ");
    scanf(" %s", time->nome);
    printf("Pontos: ");
    scanf(" %d", &time->pontos);
}

void gravarTime(Time *time){

    FILE *arq = fopen("times.txt", "w");
    if (arq == NULL){
        printf("Erro ao vriar Arquivo!!");
    }
    fprintf(arq, "%d %s %d\n", time->id, time->nome, time->pontos);

    fclose(arq);
}
void carregarTime(){
    Time *time= criarTime();

    FILE *arq = fopen("times.txt", "r");
    if (arq == NULL) {
        printf("Erro: O arquivo nao existe ou nao pode ser aberto.\n");
        free(time);
        return;
    }
    if (fscanf(arq, "%d %s %d", &time->id, time->nome, &time->pontos) != EOF) {
        printf("\n--- Dados Carregados ---\n");
        printf("ID: %d\n", time->id);
        printf("Nome: %s\n", time->nome);
        printf("Pontos: %d\n", time->pontos);
    }
    fclose(arq);
    free(time);

}

int main (){
    Time *time = criarTime();
    lerDadosTime(time);
    printf("salvando time!\n");
    gravarTime(time);
    free(time);
    printf("Resgatando times salvos!\n");
    carregarTime();

    return 0;
}