#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int repeat = 0,
        valorAtual = 1, 
        valorFuturo = 1,
        valorPassado = 1;

    printf("Informe um numero > ");
    scanf("%d", &repeat);

    for (int i = 0; i <= repeat; ++i){
        printf("%d ", valorPassado);

        valorPassado = valorFuturo;
        valorFuturo = valorFuturo + valorAtual;
        valorAtual = valorPassado;
    }

    return 0;
}