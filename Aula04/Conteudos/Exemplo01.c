// Criar um programa que aplique uma taxa de imposto de 10% para solteiros e 9% aos casados
#include <stdio.h>

int main(void){
    float salario;
    char estado_civil;

    printf("Qual o seu salario? ");
    scanf("%f", &salario);

    fflush(stdin); // Limpando memória do teclado
    printf("Vc eh casado? (C/S) ");
    estado_civil = getchar();

    if (estado_civil == 'c' || estado_civil == 'C'){
        printf("O valor da taxa que vc deve pagar eh de 9%% totalizando: R$%.2f\n", salario * 0.09);
    }
    else {
        if (estado_civil == 's' || estado_civil == 'S') {
            printf("O valor da taixa que vc deve pagar eh de 10%% totalizando: R$%.2f\n", salario * 0.10);
        }
        else {
            printf("Estado civil incorreto, por favor digite C para casado ou S para solteiro.");
        }
    }
}
