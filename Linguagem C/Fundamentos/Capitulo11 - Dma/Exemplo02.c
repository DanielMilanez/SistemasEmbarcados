#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *arq;
    unsigned char *palloc;
    unsigned long int num_bytes = 0, i = 0;
    int chr;

    arq = fopen("code.txt", "r");

    if (arq == NULL){
        printf("Falha ao abrir o arquivo.\n");
        exit(0);
    }

        printf("Arquivo aberto com sucesso!\n");

        while ((chr = fgetc(arq))!= EOF) num_bytes++;

        printf("Tamanho do arquivo %lu bytes\n", num_bytes);
        rewind(arq);

        palloc = (unsigned char *) malloc(num_bytes * sizeof(char));

        if(palloc == NULL){
            printf("Memoria insuficiente. \n");
            exit(0);
        }

        while((chr = fgetc(arq))!= EOF){
            if (i < num_bytes) palloc[i] = (unsigned char) chr;
            ++i;
        }

        for (i = 0; i < num_bytes; ++i){
            printf("%c", palloc[i]);
        }
    
    fclose(arq);
    free(palloc);

    return 0;
}