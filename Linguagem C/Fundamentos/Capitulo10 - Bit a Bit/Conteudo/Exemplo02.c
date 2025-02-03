#include <stdio.h>
#include <stdlib.h>

int main(void) {
    unsigned char firstValue = 0x16,  /*0001 0110*/
                  secondValue = 0x74, /*0111 0100*/
                  tridValue;          /*0110 0010 -- Resultado da operação*/

    printf("firstValue  :: %.2X\n", firstValue);
    printf("secondValue :: %.2X\n", secondValue);

    tridValue = firstValue & secondValue; /*Porta AND*/
    printf("tirdValue   :: %.2X -- Porta AND\n", tridValue);
    
    tridValue = firstValue | secondValue; /*Porta OR*/
    printf("tirdValue   :: %.2X -- Porta OR\n", tridValue);

    tridValue = firstValue ^ secondValue; /*Porta XOR -- Numero de entradas verdadeiras tem que ser impar*/
    printf("tirdValue   :: %.2X -- Porta XOR\n", tridValue);

    return 0;
}

/* - -- -- -- - -- -- - - -- - -- - - --- - --- - ORDEM DE PRECEDENCIA - -- - - - -- - --- -- -- -- -- -- - - -- -- --
    ~   - INVERSÃO DE BITS, complementa todos os bits, o que é 0 vira 1 e o que é 1 vira 0
    >>  - Deslocamento à direita (shift right). Desloca todos os bits para a direita, de acordo com o numero utilizado
    <<  - Deslocamento à esquerda (shift left). Desloca todos os bits para a esquerda, de acordo com o numero utilizado
    &   - Operação AND bit a bit
    ^   - Operação XOR bit a bit
    |   - Operação OR bita a bit
------------------------------------------------  ------------------   ------------------------------------------------*/