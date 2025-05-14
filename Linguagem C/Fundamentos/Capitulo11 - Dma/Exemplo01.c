/*
    Funções oriundas da stdlib.h
    malloc  :: memory alocation (solicita ao OS separar um bloco de memoria do tamanho que quisermos, retornando um ponteiro)
    free    :: libera a memória para o uso do computador.
    calloc  :: aloca o número de bytes que estou especificando, inicializando todos os endereços em 0
    realloc :: A função realloc serve para alterar durante a execução do programa o tamanho do bloque que foi alocado.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *pointter = (int *)malloc(sizeof(int));
    int *pointterWithCalloc = (int *)calloc(10, sizeof(int));

    printf("Inicializando a variavel com malloc: %d\n", *pointter);
    printf("Inicializando a variavel com calloc: %d", *pointterWithCalloc);

    printf("\nRealizando alteracoes nos valores\n");
    pointterWithCalloc[1] = 10;

    for (int i = 0; i < 10; ++i)
    {
        printf("%2d -> %2i\n", i, pointter[i]);
    }

    // Liberando a alocação da memória
    free(pointter);

    return 0;
}