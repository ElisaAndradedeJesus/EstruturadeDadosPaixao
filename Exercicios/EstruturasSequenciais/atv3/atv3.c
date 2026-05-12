// Consegui, mas queria saber ajustar quantos números 
// do double serão mostrados

// Também n sabia como mostrar float então modei pra double

#include <stdio.h>

int main() {
    float a, b, c;
    double media;
    printf("Media de 3 numeros!\n");
    printf("primenro: ");
    scanf("%f",&a);
    printf("Segundo: ");
    scanf("%f", &b);
    printf("Terceiro: ");
    scanf("%f", &c);

    media = (a + b + c)/3;
    printf("Media = %f\n", media);
}