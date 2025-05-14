/*Basicamente macros são trechos de código que podem ser subistuidos por expressões mais simples*/
#include <stdio.h>
#include <stdlib.h>

/* As operações seguem as regras de precedencia da linguagm C então tome cuidado ao inserir valores com 
multiplas operações, atente-se a ordem de precedencia*/
// #define mult(a, b) a * b

// O mais correto a se fazer é colocar parenteses em cada um dos valores.
#define mult(a, b) ((a) * (b))

int main(void){
    int resultado, resultado2;

    resultado = mult(4, 5);
    resultado2 = mult(4 - 2, 5 - 3); // Resultado esperado: 4 Resultado da saida: -9

    printf("%d\n", resultado);
    printf("%d\n", resultado2);
}

/* Macros pesam bastante na memória pois expandem o código então tome cuidado ao utilizar-se multiplas macros*/