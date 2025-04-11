#include <stdio.h>
#include <stdlib.h>

int main(void){
    FILE *arq_bin;

    arq_bin = fopen("arch3.bin","wb");

    if(arq_bin == NULL) {
        printf("ERRO\n");
        exit(2);
    }

    fputc(0xBC, arq_bin);
    fputc(0x3C, arq_bin);

    fseek(arq_bin, 0x0B, SEEK_SET);

    fputc(0xA1, arq_bin);
    fputc(0x73, arq_bin);

    fclose(arq_bin);
}