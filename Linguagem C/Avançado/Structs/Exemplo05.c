#include <stdio.h>
#include <stdlib.h>

union  contents{
    unsigned short value;
    unsigned char two_bytes[2];
};

unsigned short rec(union contents *d, FILE *arq);

int main(void) {
    FILE *arq_dat;

    union contents wr;

    wr.value = 1050;

    if (!rec(&wr, arq_dat)){
        printf("Erro ao gerar arquivo. \n");
        system("pause");
        exit(1);
    }
    printf("Sucesso!\n");

    return 0;
}

unsigned short rec(union contents *d, FILE *arq){
    if ((arq = fopen("rec.dat", "wb")) == NULL) return 0;

        fputc(d->two_bytes[0], arq);
        fputc(d->two_bytes[1], arq);

    fclose(arq);
    return 1;
}
