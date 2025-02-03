// Utilização de operador ternário em C
#include <stdio.h>

int main(void){
    float salario;

    printf("Qual o seu salario: ");
    scanf("%f", &salario); // Não esquecer do elo entre a função e a variável '&'

    // Fazendo verificação em uma única estutura condicional, utilizando por meio um operador ternário.
    salario = salario > 1000 ? salario * 1.05 : salario * 1.07;
    printf("Seu novo salario sera de: R$%.2f\n", salario);
}
