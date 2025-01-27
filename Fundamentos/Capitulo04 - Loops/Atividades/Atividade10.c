// Sequencia de fibonacci
#include <stdio.h>
#include <stdbool.h>
#include <stdbool.h>

int main(void) {
    int numAtual = 1,
        proxNum = 1,
        troca,
        limite;

    printf("Informe o limite da sequencia de fibonacci >> ");
    scanf("%d", &limite);

    printf("Sequencia de fibonacci.\n");

    while (true){
        printf("%d ", numAtual);
        if (numAtual > limite) break;

        troca = proxNum;
        proxNum = numAtual + proxNum;
        numAtual = troca;
    }
    
}