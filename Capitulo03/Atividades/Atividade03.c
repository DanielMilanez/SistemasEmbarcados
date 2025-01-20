#include <stdio.h>

int main(void){
    unsigned short int idade; 
    char possuiCarro;

    printf("Sua idade: ");
    scanf("%hu", &idade);

    fflush(stdin);

    printf("Vc possui carro? ");
    scanf("%c", &possuiCarro);

    if (possuiCarro == 's' || possuiCarro == 'S'){
        printf("Vc recebe R$200 de vale transporte, independente de sua idade");
    } else {
        if (idade >= 18 && idade <= 50){
            printf("Vc recebe R$500 de vale transporte");
        } else if (idade < 18) {
            printf("Vc possui R$200 de vale transporte");
        }
    }
}