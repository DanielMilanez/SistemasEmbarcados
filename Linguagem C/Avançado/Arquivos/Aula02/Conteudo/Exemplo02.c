#include <stdio.h>
#include <stdlib.h>

#define DIM 10

int main(void){
    FILE *arq;
    char vec[DIM];

    arq = fopen("info.bin", "rb");

    if (arq == NULL){
        printf("Erro\n");
        exit(1);
    }

    fread(vec, sizeof(vec[0]), 10, arq);

    for(int i = 0; i < DIM; ++i){
        printf("%d ", vec[i]);
    }

    fclose(arq);
}