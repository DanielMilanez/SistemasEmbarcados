#include <stdio.h>

int main(void){
    int count, ramos, numeroLetra;
    char letra = 'A';

    printf("Informe a quantidade de ramos que vc deseja: ");
    scanf("%d", &ramos);

    numeroLetra = (int)letra;

    for (int i = 0; i <= ramos; i++){
        for (int j = 0; j <= count; j++){
            printf("%c", (char)numeroLetra);
        }
        numeroLetra++;
        count++;
        printf("\n");
    }
}