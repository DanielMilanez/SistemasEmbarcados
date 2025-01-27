#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void escreva(char letter, FILE *new_file);

int main(void) {
    FILE *new_file;
    char letter = 'A';

    // Abrir o arquivo!
    new_file = fopen("teste.txt", "w");

        system("cls");

        if (new_file == NULL) puts("ERRO: Falha na leitura do arquivo.");
        else puts("Arquivo lido com sucesso!");

        for (int i = 0; i < 30; ++i){
            escreva(letter, new_file);
        }

    // Fechar o arquivo
    fclose(new_file);
}

void escreva(char letter, FILE *new_file){
    fputc('\n', new_file);
    for (int i = 0; i < 26; ++i){
        fputc((short) letter + i, new_file);
        fputc(' ', new_file);
    }

    fputc('\n', new_file);

    for (int i = 0; i < 26; ++i){
        fputc(i + 32, new_file);
        fputc(' ', new_file);
    }
}