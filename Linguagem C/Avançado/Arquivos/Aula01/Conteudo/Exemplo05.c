#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    FILE *arq_r, *arq_w;
    int ch;

    system("cls");

    if ((arq_r = fopen("teste.txt", "r")) == NULL){
        puts("ERRO1: Falha na leitura do arquivo.");
    }

    if ((arq_w = fopen("novo.txt", "w")) == NULL){
        puts("ERRO2: Falha na leitura do arquivo.");
    }

    fputs("Teste de escrita no arquivo.", arq_w);
        
    fclose(arq_r);      
    fclose(arq_w);

    printf("\nArquivo replicado com sucesso!");

    return 0;
}
