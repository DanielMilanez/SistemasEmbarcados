#include <stdio.h>
#include <stdlib.h>

#define TAM 10

int main(void) {
    int number[TAM] = {0},
        num,
        maior,
        menor;

    for (int i = 0; i < TAM; ++i){
        printf("Insira o %d numero : ", i);
        scanf("%d", &num);
        number[i] = num;

        if (number[i] > maior) maior = number[i];
        if (number[i] < menor) menor = number[i];
    }

    printf("\nO maior valor digitado foi: %d", maior);
    printf("\nO menor valor digitado foi: %d", menor);

    return 0;
}