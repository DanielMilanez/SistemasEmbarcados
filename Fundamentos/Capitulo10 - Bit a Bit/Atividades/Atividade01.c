#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void showTable(unsigned char out, unsigned char temperature);
void printb(unsigned char input,  unsigned char temperature);
void protocolLoad(unsigned char *out, unsigned char erro, unsigned char sing, unsigned char uni);

struct sensor {
    unsigned char P0 : 1;   
    unsigned char P1 : 1;
    unsigned char P2 : 1;
    unsigned char P3 : 1;
    unsigned char P4 : 1;
    unsigned char P5 : 1;
    unsigned char P6 : 1;
    unsigned char P7 : 1;
}protocol;

int main(void) {
    unsigned char out,
                  sing,
                  uni,
                  erro = 0;

    char newTemp[10] = {0},
         auxString[10] = {0};

    int temp = 0;

    printf("Informe a temperatura >> ");
    gets(newTemp);

    for (int i = 0; newTemp[i] != '\n'; ++i){
        switch (newTemp[i]){
            case '-':
                sing = 1;
                break;

            case 'F':
                uni = 1;
                break;

            default:
                break;
        }
    }

    // int i = 1;

    // for (i = 1; newTemp[i] != '\n'; ++i){
    //     if (isdigit(newTemp[i])){
    //         newTemp[i] = auxString[i];
    //     }
    // }
    // auxString[i] = '\n';

    // puts(auxString);
    // temp = atoi(auxString);
    // printf("Valor em decimal de temp: %d\n", temp);

    // protocolLoad(&out, erro, sing, uni);
    // showTable(out, (char)temp);
}

void showTable(unsigned char out, unsigned char temperature){

    printf(" -------------------------------------------------\n");
    printf(" |  protocolo        erro  sig uni | temperature |\n");
    printf(" |-------------------------------- | ----------- |\n");
    printb(out, temperature);
    printf(" -------------------------------------------------\n");
}

void printb(unsigned char protocol, unsigned char temperature){
    for (int i = 7; i >= 0; --i){
        if (i == 3) putchar(' ');
        (protocol >> i) & 1 ? printf("   1") : printf("   0");
    }printf("  | ");

    for (int i = 7; i >= 0; --i){
        if (i == 3) printf("   ");
        (temperature >> i) & 1 ? printf("1") : printf("0");
    }printf(" |\n");
}

void protocolLoad(unsigned char *out, unsigned char erro, unsigned char sing, unsigned char uni){
    /* 1010 00 0 0 */
    *out = (protocol.P5 = 1) << 5 |
           (protocol.P7 = 1) << 7;

    if (erro){
        *out ^= 0x8;
        *out ^= 0x4;
    }

    if (sing){
        *out ^= 0x2;
    }

    if (uni){
        *out ^= 0x1;
    }
}
