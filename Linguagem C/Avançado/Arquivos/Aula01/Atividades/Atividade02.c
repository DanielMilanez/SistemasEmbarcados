#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *my_file, *my_result;

    char file_name[30];

    int ch;

    printf("Informe o nome do arquivo >> ");
    gets(file_name);

    if ((my_file = fopen(file_name, "r")) == NULL){
        puts("ERRO FATAL.");
        system("PAUSE");
        exit(0);
    }

    if ((my_result = fopen("resultado.txt", "w")) == NULL){
        puts("ERRO");
        system("PAUSE");
        exit(0);
    }

    while ((ch = fgetc(my_file)) != EOF){
        ch -= 3;
        fputc(ch, my_result);
    }

    puts("Processo concluido!");

    fclose(my_file);
    fclose(my_result);
}

