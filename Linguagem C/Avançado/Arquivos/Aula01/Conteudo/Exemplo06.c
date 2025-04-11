#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *arq;
    char s[20];

    printf("Digite o nome do arquivo: ");
    gets(s);

    arq = fopen(s, "w");
        if (arq == NULL) printf("ERRO\n");

       fputs("Escrita de string no arquivo\n", arq);
    fclose(arq);

    arq = fopen(s, "r");
        if (arq == NULL) printf("ERRO\n");

        if (fgets(s, 200, arq)) printf(s);
    fclose(arq);

}