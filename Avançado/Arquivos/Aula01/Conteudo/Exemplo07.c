#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *arq;
    char s[20];
        // , ch;

    printf("Digite o nome do arquivo: ");
    gets(s);

    arq = fopen(s, "w");
        if (arq == NULL) printf("ERRO\n");

        // while ((ch = fgetc(arq)) != EOF){
        //     printf("%c", ch);
        // }
        fputs("Escrita em arquivo externo.", arq);
    fclose(arq);
}