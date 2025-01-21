/* Este arquivo pertece ao exemplo 04 */
#include <stdio.h>
#include <stdlib.h>

extern void resultado();

int valor  = 3,
    numero = 1,
    teste  = 2;

int main(void) {
    resultado();
    return 0;
}

/*
    A linkagem de arquivos é realizada atraves processo de compilação, o comando extern
    funciona dependentemente deste processo, no qual o compilador correlaciona os arquivos
    que estão sendo compilados e as chamadas desta função durante seu processo de compilação

    como o vscode por padrão não compila seus arquivos ou gera um exe apenas
    executandoos, esse processo nunca iria funcionar aqui, por isso precisamos compilar 
    manualmente utilizando o gcc!

    para isso acesse o diretório do arquivo ou arquivos que deseja compilar e digite o nome dele e o nome 
    do executavel que será gerado

    no nosso caso os arqivos foram main.c e resultado.c

    gcc main.c resultado.c -o program.exe
*/