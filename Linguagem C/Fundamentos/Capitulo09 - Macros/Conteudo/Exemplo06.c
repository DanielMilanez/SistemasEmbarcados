#include <stdio.h>
#include <stdlib.h>

#define show(str) printf(#str)
#define VAR(str) n##str

int main(void) {
    int n1 = 100,
        n2 = 200,
        n3 = 300,
        n4 = 400,
        n5 = 500;
    
    system("cls");
    show(ola mundo usando uma macro para escrever esta frase\nsem usar aspas muito legal nao e?);

    printf("\n\nAcessando valoers usando uma macro e o operador ##\n\n");
    printf("%d\n", VAR(1));
    printf("%d\n", VAR(2));
    printf("%d\n", VAR(3));
    printf("%d\n", VAR(4));
    printf("%d\n", VAR(5));
    
    return 0;
}

/* -----------------------------------------------------------------------------------
    O operador hastag é utilizdo para fornecer flexibilidade a escrita de macros     |
    o ituito é utilizar ele antes de um parametro de uma macro, desta forma torna-se |
    desnecessário a utilização de aspas na expressão caso seja uma string            |
------------------------------------------------------------------------------------ */

/* -----------------------------------------------------------------------------------
    Agora para a utilização de dois hastags permite a concatenação de duas strings a |
    expressão sem a necessidadde de incluir adição de aspas ou tratamento de         |
    caracteres especiais                                                             |
------------------------------------------------------------------------------------ */   

/* -------------------------------------------------------------------------------------
    O caractere cardinal "#" utilizado no inicio de cada instrução direta ao pré       | 
    processador, sendo assim, todas as instruções também precedidas com este caractere |
                                                                                       |
    Exemplos:                                                                          |
                                                                                       |
    #define                                                                            | 
    #include                                                                           |
        .                                                                              |
        .                                                                              |
        .                                                                              |
------------------------------------------------------------------------------------- */   
