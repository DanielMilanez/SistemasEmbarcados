#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DIM 5

int main(void) {
    int list[DIM] = {0},
        meuValor,
        trocou,
        tempNumber,
        count = 0;

    for (int i = 0; i < DIM; ++i){
        printf("Informe o %d numero: ", i + 1);
        scanf("%d", &meuValor);

        list[i] = meuValor;
    }

    while (true){
        trocou = false;

        for (int i = 0; i < DIM - 1; i++){  
            if (list[i] > list[i + 1]){  

                tempNumber = list[i];
                list[i] = list[i + 1];
                list[i + 1] = tempNumber;

                trocou = true;
                count++;    
            }
        } 
        
        if (!trocou) break;  
    }


    printf("Houve %d trocas\n", count);

    printf("Lista ordenada: ");
    for (int i = 0; i < DIM; ++i){
        printf("%d ", list[i]);  
    }
    printf("\n");

    return 0;
}
