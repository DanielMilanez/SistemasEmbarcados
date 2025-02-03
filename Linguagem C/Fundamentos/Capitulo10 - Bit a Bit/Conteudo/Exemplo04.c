/*Operadores bit a bit podem ser utilizados no conceito de máscara de bits. São
aplicados quando desejamos preservar ou remover, concatenar ou inverter bits
pontuais. Para preservar/remover, utilizamos o operador AND(&). */
#include <stdio.h>
#include <stdlib.h>
#include "LeitorDeBits.c"

int main(void) {

    unsigned char registro = 0x32;

    printb(registro);
    putchar('\n');

    registro &= 0xF0;
    printb(registro);

    return 0;
}