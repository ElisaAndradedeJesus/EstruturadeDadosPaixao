#include <stdio.h>

int main() {
    int num;
    printf("Informe um número inteiro maior que zero!\n");
    printf("numero: ");
    scanf("%d", &num);

    while(num <= 0) {
        printf("O numero precisa ser maior que zero!\n");
        printf("numero: ");
        scanf("%d", &num);
    }
    if (num % 2 == 0) {
        printf("É Par!\n");
    } else {
        printf("É impar!\n");
    }
    return 0;
}