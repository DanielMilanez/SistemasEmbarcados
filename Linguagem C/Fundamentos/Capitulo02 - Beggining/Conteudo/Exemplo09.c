// Trabalhando com números hexadecimais

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int value = 0;
    /*
        LEMBRANDO DE QUE 
        DEC: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
        HEX: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,  A,  B,  C,  D,  E,  F
    
    */

    printf("%X --- ", 0xA); // Imprime em letras maiúsuclas
    printf("%x\n", 0xA); // Imprime em letras minusculas

    // Realizando operações aritimeticas com hexa e dec
    printf("\nOp.\n");
    printf("DEC - %d + %d\nHEX - %X + %X\n", 0xB3, 2, 0xB3, 2);
    printf("Result.\n");
    printf("DEC %d\nHEX %X\n", 0xB3 + 2, 0xB3 + 2);    

    printf("\nOp.\n");
    printf("DEC - %d + %d\nHEX - %X + %X\n", 0xA2, 10 , 0xA2, 10);
    printf("Result.\n");
    printf("DEC %d\nHEX %X\n", 0xA2 - 10, 0xA2 - 10);    

    printf("\nOp.\n");
    printf("DEC - %d * %d\nHEX - %X * %X\n", 0xB3, 2, 0xB3, 2);
    printf("Result.\n");
    printf("DEC %d\nHEX %X\n", 0xB3 * 2, 0xB3 * 2);    

    printf("\nOp.\n");
    printf("DEC - %d / %d\nHEX - %X / %X\n", 0xA, 2, 0xA, 2);
    printf("Result.\n");
    printf("DEC %d\nHEX %X\n", 0xA / 2, 0xA / 2);    

    printf("\n===============\n");
    printf("Agora trabalhando com incert de dados\n");
    printf("Insira um valor em hexadecimal (ex: 0xA3) >> ");
    scanf("%X", &value);
    fflush(stdin);

    printf("O valor digitado em Hexadecimal convertido para Dec eh: %d", value);
}
