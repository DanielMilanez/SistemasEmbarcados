#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *arq;

    int vec[3] = {3, 14, 4};

    if((arq = fopen("info.dat", "wb")) == NULL){
        printf("ERRO\n");
        system("pause");
        exit(1);
    }

    fwrite(vec, sizeof(vec), 4, arq);
    fclose(arq);
}