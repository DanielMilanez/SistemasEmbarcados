#include <stdio.h>
#include <stdlib.h>

int main(void) {
    unsigned char registro = 0x80; /*1000 0000b*/

    printf("%.2X\n", registro);
    // registro = ~registro; /*inverte as coisas, o que era 0 vira 1 e o que era 1 vira 0 -- NOT*/

    /*Antes --- 1000 0000 */
    registro = registro >> 1; /*Depois --- 0100 0000*/
    printf("%.2X\n", registro);

    registro = registro >> 2; /*Depois --- 0010 0000*/
    printf("%.2X\n", registro);

    registro = registro << 4; /*Depois --- 00000000*/
    printf("%.2X\n", registro);

    return 0;
}