/*Utilizando expressões com mais linhas em uma macro*/
#include <stdio.h>
#include <stdlib.h>

/*Indicando ao pre processador que a macro continua na linha seguinte utilizando o "\" */
#define hello printf("Hello "); \
              printf("World! ");\
              printf("Yes!!!\n")

int main(void){
    hello;
}