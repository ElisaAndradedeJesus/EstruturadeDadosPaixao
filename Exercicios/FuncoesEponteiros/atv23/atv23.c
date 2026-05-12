#include <stdio.h>

float calcular_bonus(int anos_trabalho, float salario){
    if(anos_trabalho > 5 && salario > 5000)
        return 0.1 *salario;
    
    return 0.05 * salario;
}

int main (){
    int anos_trabalho;
    float salario, bonus;

    printf("Insira salário e tempo deserviço: ");
    scanf("%f %d",&salario, &anos_trabalho);
    
    bonus = calcular_bonus(anos_trabalho,salario);
    printf("Bonus: %.2f\n",bonus);

    return 0;
}