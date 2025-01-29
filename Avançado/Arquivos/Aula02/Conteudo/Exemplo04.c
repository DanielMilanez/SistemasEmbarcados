/* Selecionando uma região expecifica do arquivo*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *arq_bin;

    if ((arq_bin = fopen("arq2.bin", "wb")) == NULL) exit(0);
    puts("Processo info.dat concluido!");

    fputc(0xAA, arq_bin);
    fputc(0xAB, arq_bin);
    fputc(0xAC, arq_bin);
    fputc(0xAD, arq_bin);

    printf("End. Atual: %ld\n", ftell(arq_bin));
    rewind(arq_bin);
    printf("End. Atual: %ld\n", ftell(arq_bin));
    
    fclose(arq_bin);
}
