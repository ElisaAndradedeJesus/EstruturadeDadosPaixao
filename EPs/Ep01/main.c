#include <stdio.h>

int main () {
    int jogador1, jogador2;
    printf("Bem vindo a Pedra Papel e Tesoura!\n");
    printf("Pedra será 0\nPapel será 1\nTesoura será 2\n");
    printf("Cada Jogador deve escolher apenas uma opção entre as três opções acima.\n");
    printf("Jogador 1: ");
    scanf("%d", &jogador1);
    printf("Jogador 2: ");
    scanf("%d", &jogador2);

    if (jogador1 == jogador2) {
        printf("Empate!\n");
    } else if ((jogador1 == 0 && jogador2 == 2) || (jogador1 == 1 && jogador2 == 0) || (jogador1 == 2 && jogador2 == 1)) {
        printf("Jogador 1 venceu!\n");
    } else {
        printf("Jogador 2 venceu!\n");
    }

    return 0;
}