#include <stdio.h>
#include <stdlib.h>

// A função realloc serve para alterar durante a execução do programa o tamanho do bloque que foi alocado.
// Lembrando que caso não seja possível estender o espaço já alocado na memória, outro será selecionado e o qu estava em uso anteriormente será liberado (free). 

int main(void){
    int * pointter = (int *) calloc(2, sizeof(int));
    *pointter = 10;
    pointter[1] = 20;
    
    int * pointter_copy = (int *) realloc(pointter, 3 * sizeof(int));
    pointter_copy[2] = 30;

    for (int i = 0; i < 3; ++i){
        printf("%d\n", pointter_copy[i]);
    }
    return 0;
}