#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    FILE *arq;
    // char minha_frase[31];

    /*Variável para armazenar chars do arquivo lido*/
    int ch;

    arq = fopen("teste.txt", "r");

        system("cls");
        if (arq == NULL) puts("ERRO: Falha na leitura do arquivo.");
        else puts("Arquivo lido com sucesso!");

        // printf("Informe a frase para o arquivo >> ");
        // gets(minha_frase);
        // fflush(stdin);

        /*Ao trabalhar com arquivos em C estamos sempre trabalhando com strings*/
        // for (int i = 0; i <= (int)strlen(minha_frase); ++i){
        //     if (minha_frase[i] == '\0') break;
        //     else fputc(minha_frase[i], arq);
        // }
        // fputc('\n', arq);
        // fputc('\n', arq);

        // for (int i = 0; i < 30; ++i){
        //     for (int j = 0; j < 30; ++j){
        //         fputc(j + 48, arq);
        //     }
        //     fputc('\n', arq);
        // }

        /*Lendo arquivo*/

        // printf("%c\n", fgetc(arq));
        // printf("%c\n", fgetc(arq));
        // printf("%c\n", fgetc(arq));
        // printf("%c\n", fgetc(arq));

        /*STDIO FORNEÇE A FUNÇÃO EOF (END OF FILE)*/
        while((ch = fgetc(arq)) != EOF){
            printf("%c", ch);
        }

    fclose(arq);
    return 0;
}
