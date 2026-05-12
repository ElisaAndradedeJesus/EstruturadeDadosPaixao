// Versão sugerida: mantém a lógica original, adiciona validação de entrada e usa maior2 de forma direta.

#include <stdio.h>

int maior2(int a, int b) {
    if (a > b) return a;
    return b;
}

int maior3(int a, int b, int c) {
    return maior2(maior2(a, b), c);
}

int main(void) {
    int a, b, c;
    printf("Insira 3 números: ");
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        fprintf(stderr, "Entrada inválida\n");
        return 1;
    }
    printf("a: %d b: %d c: %d\n", a, b, c);
    printf("Maior: %d\n", maior3(a, b, c));
    return 0;
}
