#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    FILE *arq_r, *arq_w;
    int ch, count = 0;

    if ((arq_r = fopen("teste.txt", "r")) == NULL){
        puts("ERRO1: Falha na leitura do arquivo.");
    }

    if ((arq_w = fopen("resultado.txt", "w")) == NULL){
        puts("ERRO2: Falha na leitura do arquivo.");
    }

    while ((ch = fgetc(arq_r)) != EOF){
        printf("%c", ch);

        if (ch != 'b' && ch != 'B') fputc(ch, arq_w);

    } ++count;
        
    fclose(arq_r);      
    fclose(arq_w);

    printf("\nO arquivo tem %d linhas\n", count);

    return 0;
}
