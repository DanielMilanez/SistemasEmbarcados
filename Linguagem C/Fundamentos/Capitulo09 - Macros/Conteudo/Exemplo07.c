#include <stdio.h>
#include <stdlib.h>

#define DEBUG

void exibeInfo();

int main(void) {

    int i, n = 0;

    // #undef DEBUG

    // #ifndef DEBUG
    //     puts("Debug: DESATIVADO");
    // #endif

    for (i = 0; i < 10; ++i){
        n += i;

        #ifdef DEBUG
            printf("DEBUG Info:\ni = %d\nn = %d\n", i, n);

        #endif
    }
    
    printf("Resultado : %d", n);
    puts("\n\n\n");
    puts("---------------------");
    exibeInfo();

    return 0;
}


/* -------------------------------------------------------------------------
    Diretiva #ifdef verifica se um determinado símbolo está definido       |
    Diretiva #ifndef verifica se um determinado símbolo não está definido  |
    Diretiva #undef retira a definição de um símbolo.                      |
------------------------------------------------------------------------- */


/* ----------------------------------------------------------------------------
    Operador defined() quando integrado em um #if funciona da mesma forma que |
    um #ifdef                                                                 |
                                                                              |
    Mas a utilização desse operador permite a utilização de expressões mais   |
    complexas.                                                                |
                                                                              |
    Ex.:                                                                      |
    #if defined(Este_simbolo) && !defined(Outro_simbolo)                      |
----------------------------------------------------------------------------- */


// Line pode informar em qual linha estamos do código. Assim como podemos definir
// a linha em que estamos

/*
    Diretiva ERRO é normalmente colocada em uma instrução condicional, permitindo
    obter um erro gerado pelo pré-processador com um formado do tipo.

    Error: filename line# : Error directive: errormsg
*/

/*
    Diretiva PRAGMA, utilizada para dizer qual o tipo de alinhamento dos dados
    dentro de uma estrutura.
*/

/*
    Macros predefinidas: A norma ansi define a obrigatoriedade da existência nos pré-
    processadores(compiladores) um conjunto de macros predefinidas, essa smacros tem 
    dois underscores __ á esquerda e outros dois a direita.

    __DATE__ String no formato "MM DD YYYY"
    __TIME__ String no formato "HH:MM:SS"
    __LINE__ Valor numerico com o número da linha atual. O valor pode ser alterado através da #line
    __FILE__ String com o nome do arquivo atual
*/

void exibeInfo(){
    printf("Arquivo      : %s\n", __FILE__);
    printf("Data atual   : %s\n", __DATE__);
    printf("Hora atual   : %s\n", __TIME__);
    printf("Linha atual  : %d\n", __LINE__);
    #line 1234
    printf("Nova linha   : %d", __LINE__);
}