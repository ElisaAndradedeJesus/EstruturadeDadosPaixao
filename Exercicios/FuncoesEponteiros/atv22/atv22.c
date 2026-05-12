// Implemente a função maior3 que recebe três inteiros e retorna o maior valor dentre eles. A
// função deve se apoiar, estritamente, na função maior2, ou seja, não pode utilizar o comando if
// ou while.

#include <stdio.h>

int maior2(int a,int b) {
    if (a > b){
        return a;
    }
    return b;
}

int maior3 (int a, int b, int c) {
    int maiorAB = maior2(a,b);
    int maiorBC = maior2(b,c);
    int maior = maior2 (maiorAB,maiorBC);
    return maior;
}

int main () {
    int a,b,c,maior;
    printf("insira 3 númeoros: ");
    scanf("%d %d %d", &a, &b, &c);
    printf(" a:%d b:%d c:%d\n", a, b, c);
    

    maior = maior3(a,b,c);
    printf("Maior: %d\n",maior);
    return 0;
}