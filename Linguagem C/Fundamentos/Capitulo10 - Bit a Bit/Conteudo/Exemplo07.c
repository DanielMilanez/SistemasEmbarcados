#include <stdio.h>
#include <stdlib.h>

/*Os campos de bits são uma extensão das funcionalidades das estruturas em C e sua
aplicação se dá quando desejamos mapear registradores em microcontroladores ou mesmo ter
informações de um único bit em nosso código. No Box 8 vemos a sintaxe da declaração de um
campo de bits.*/

struct reg{
    unsigned P0 : 1;
    unsigned P1 : 1;
    unsigned P2 : 1;
    unsigned P3 : 1;
    // unsigned    : 4; /*Deixei os bits anteriores como insignificantes, trabalhando assim so com os MSBs*/
    unsigned P4 : 1;
    unsigned P5 : 1;
    unsigned P6 : 1;
    unsigned P7 : 1;
}PORT;


int main(void) {
    unsigned char outp;

    PORT.P0 = 1;
    PORT.P6 = 1;

    outp = PORT.P0     |
           PORT.P1 << 1|
           PORT.P2 << 2|
           PORT.P3 << 3|
           PORT.P4 << 4|
           PORT.P5 << 5|
           PORT.P6 << 6| 
           PORT.P7 << 7; 

    printf("%Xh\n", outp);

    return 0;
}
