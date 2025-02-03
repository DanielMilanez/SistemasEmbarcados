#include <stdio.h>
#include <stdlib.h>

int main(void){
    FILE *arq_dat, *arq_bin;
    int ch;

    if ((arq_dat = fopen("info.dat", "rb")) == NULL) exit(0);
    puts("Processo info.dat concluido!");

    if ((arq_bin = fopen("arq.bin", "wb")) == NULL) exit(0);
    puts("Processo arq.bin concluido!");

        while (!feof(arq_dat)){
            ch = fgetc(arq_dat);

            if (!feof(arq_dat)){
                fputc(ch, arq_bin);
            }
        }
    
    fclose(arq_bin);
    fclose(arq_dat);

    puts("Arquivo copiado com sucesso\n");
}
