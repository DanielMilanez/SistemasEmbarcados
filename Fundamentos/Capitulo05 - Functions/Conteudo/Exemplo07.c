#include <stdio.h>
#include <stdlib.h>

/*Recursividade de funções >> Chamar funções de maneira recursiva demanda mais espaço de memória
o lado positivo é que conseguimos realizar a repetição de código sem a utilização de um laço de 
repetição. */

void downToZero(int number);

int main(void) {
    int number = 0;

    printf("Informe um numero >> ");
    scanf("%d", &number);
    fflush(stdin);
    
    downToZero(number);
    puts("Fim da contagem...");
    return 0;
}

void downToZero(int number){
    if (number <= 0) return; // Invalidando as chamadas!
    printf("%3d\n", number);
    downToZero(--number); 
}