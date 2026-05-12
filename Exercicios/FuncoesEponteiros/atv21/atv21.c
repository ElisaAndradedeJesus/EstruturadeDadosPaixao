#include <stdio.h>

int quadrado (int x) {
    return x*x;
}

int main() {
    int num;
    printf("numero: ");
    scanf("%d",&num);
    int q = quadrado(num);
    printf("Quadrado: %d\n",q);
    
    return 0;
}