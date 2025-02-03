// Exemplo da fução concat
#include <stdio.h>
#include <string.h>

#define DIM 20
#define SEP_NOME ", "

int main(void){
    char nome[DIM + 1], sobrenome[DIM + 1], complemento[2 * DIM + 1];
    while(1){
        printf("Nome: "); gets(nome);
        if (strlen(nome) == 0) break;

        printf("Sobrenome: "); gets(sobrenome);
        
        strcpy(complemento, sobrenome);
        strcat(complemento, SEP_NOME);
        strcat(complemento, nome);

        puts(complemento);
    }
}