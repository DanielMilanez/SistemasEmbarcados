// Faça a contagem de 5 em 5 de um número ate 50
#include <stdio.h>

int main(void){
    int n = 1;

    while (n <= 10){ 
        /* 2d representa que são necessários 2 caracteres para representar o número
            quando o número a esquerda não existe são colocados espaços. */
        printf("5 * %2d = %2d\n", n, 5 * n); 
        n += 1;
    }
}
