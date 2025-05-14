#include <stdio.h>
#include <stdlib.h>
#include "LeitorDeBits.c"

int main(void) {

    unsigned char reg = 0xAB;

    printf("\n%X\n", reg);
    printf("reg: ");
    printb(reg); /*10101011*/

    reg ^= 0x04; /*00000100*/

    printf("\n%X\n", reg); /*10101111*/
    printf("\n%d\n", reg);
    printf("reg: ");
    printb(reg);

    return 0;
}