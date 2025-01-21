#include <stdio.h>
#include <stdlib.h>

int main(void){
    char estadoCivil;
    unsigned short int idade;

    system("cls");

    printf("\n\t\t=====================================");
    printf("\n\t\t\tInforme seu estado civil!");
    printf("\n\t\t\ts - para solteiro");
    printf("\n\t\t\tc - para casado");
    printf("\n\t\t\td - para divorciado");
    printf("\n\t\t\tv - para viuvo");

    printf("\n\t\t=====================================");
    printf("\n\t\tselecione: ");
    scanf("%c", &estadoCivil);
    fflush(stdin);

    printf("\n\t\t======================================");
    printf("\n\t\tinforme sua idade: ");
    scanf("%hu", &idade);
    printf("\n\t\t======================================\n\n");

    system("cls");

    switch (estadoCivil){
        case 's':
            printf("O individuo tem %hu e eh solteiro", idade);
            break;

        case 'c':
            printf("O individuo tem %hu e eh casado", idade);
            break;

        case 'd':
            printf("O individuo tem %hu e eh divorciado", idade);
            break;

        case 'v':
            printf("O individuo tem %hu e eh viuvo", idade);
            break;
        
        default:
            printf("Entrada de valores invalidos!");
            break;
    }
}