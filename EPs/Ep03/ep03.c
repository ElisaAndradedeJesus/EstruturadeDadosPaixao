#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define N 5

char jogadaPC(void) {
    int random = rand() % 100;
    if (random <= 50) return 'R';
    if (random <= 75) return 'P';
    return 'S';
}

char winner(char j, char p) {
    if (j == p) return 'E';
    if ((j == 'R' && p == 'S') ||
        (j == 'S' && p == 'P') ||
        (j == 'P' && p == 'R')) return 'V';
    return 'D';
}

int main(void) {
    char j, p;
    int vitorias = 0, derrotas = 0, empates = 0;

    srand((unsigned)time(NULL));

    printf("Rock Papel Scissor!\nR=Rock P=Paper S=Scissor\n");

    for (int i = 0; i < N; i++) {
        printf("Player: ");
        if (scanf(" %c", &j) != 1) break;   // note o espaço antes de %c
        j = toupper((unsigned char)j);

        if (j != 'R' && j != 'P' && j != 'S') {
            printf("Entrada inválida, tente novamente.\n");
            i--; continue;
        }

        p = jogadaPC();
        printf("PC jogou: %c\n", p);

        char res = winner(j, p);
        if (res == 'V') vitorias++;
        else if (res == 'E') empates++;
        else derrotas++;
    }

    printf("Vitorias: %d\nDerrotas: %d\nEmpates: %d\n", vitorias, derrotas, empates);
    return 0;
}