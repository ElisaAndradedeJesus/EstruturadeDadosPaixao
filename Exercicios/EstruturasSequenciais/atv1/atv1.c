// Faça um programa que leia a temperatura em graus Fahrenheit (F), converta-a 
// para graus Celsius e mostre a temperatura convertida na tela. 


#include <stdio.h>

int main (){
    float far, cel;
    printf("Conversor Fahrenheit para Celsius.\nTemperatura Fahrenheit: ");
    scanf("%f", &far);
    cel = 5 * (far - 32)/9;
    printf("Temperatura em Celsius: %.2f", cel);

    return 0;

}