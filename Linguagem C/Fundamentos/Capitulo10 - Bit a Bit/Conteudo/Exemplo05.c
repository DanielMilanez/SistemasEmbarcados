#include <stdio.h>
#include <stdlib.h>
#include "LeitorDeBits.c"

#define nw putchar('\n');

int main(void) {

    unsigned char byte1 = 0x45,
                  byte2 = 0x6E,
                  byte3;

    puts("Bytes originais: ");
    printf("byte 1 > ");
    printb(byte1);
    nw

    printf("byte 2 > ");
    printb(byte2);
    nw
    nw

    puts("Bytes depois da mascara: ");
    byte1 &= 0x0F;
    byte2 &= 0xF0;

    printf("byte 1 > ");
    printb(byte1);
    nw

    printf("byte 2 > ");
    printb(byte2);
    nw
    nw

    puts("Bytes concatenados");
    byte3 = byte1 | byte2;
    printf("byte3 > ");
    printb(byte3);
    nw
    printf("byte3 > %Xh \n", byte3);

    return 0;
}