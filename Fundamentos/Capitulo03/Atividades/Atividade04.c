// Calcular programa que calcule o imposto pago por homens e mulheres
// Mulheres pagam 10% e homens pagam 15%

#include <stdio.h>

int main(void){
    float salario, imposto;
    char sexo;

    printf("Informe seu salario: ");
    scanf("%f", &salario);

    fflush(stdin);

    printf("Informe seu sexo: ");
    scanf("%c", &sexo);

    switch (sexo){
        case 'F':
        case 'f':
            imposto = 0.10;
            break;

        case 'M':
        case 'm':
            imposto = 0.15;
            break;
        
        default:
            printf("Entradas invalidas! Digite apenas F ou M!");
    }    

    printf("O valor total a ser pago eh: R$%.2f", imposto * salario);

}
