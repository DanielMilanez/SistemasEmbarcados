#include <stdio.h>
#include <stdlib.h>
#include "LeitorDeBits.c"

int main(void) {
    unsigned char first_val = 0x1A,
                  second_val = 0xFF,
                  result;

    printf("Valores binarios para a analise\n\n");
    printf("Primeiro valor >> %.2X -- B ", first_val);
    printb(first_val);
    putchar('\n');

    printf("Segundo valor  >> %.2X -- B ", second_val);
    printb(second_val);

    putchar('\n');
    putchar('\n');
    putchar('\n');

    result = first_val & second_val; /*Porta AND*/
    printf("result   :: %.2X -- B ", result);
    printb(result);
    printf("  -- AND\n");
    
    result = first_val | second_val; /*Porta OR*/
    printf("result   :: %.2X -- B ", result);
    printb(result);
    printf("  -- OR\n");

    result = first_val ^ second_val; /*Porta XOR -- Numero de entradas verdadeiras tem que ser impar*/
    printf("result   :: %.2X -- B ", result);
    printb(result);
    printf("  -- XOR\n");
    
    return 0;
}