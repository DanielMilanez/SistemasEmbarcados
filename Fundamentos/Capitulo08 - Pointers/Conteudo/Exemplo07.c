#include <stdio.h>
#include <stdlib.h>

#define DIM 11

int main(void) {
    long first_vetor[DIM] = {10, 4, 29};
    short second_vetor[DIM] = {5, 5, 7};

    long *ptr_fvetor = first_vetor;
    short *ptr_svetor  = second_vetor;

    for (int i = 0; i < DIM; ++i){
        *(ptr_fvetor + i) = 2 * i;
        *(ptr_svetor + i) = 3 * i;
    }

    printf("First vector --- Second vector\n");
    for (int i = 0; i < DIM; ++i){
        printf("\t%2ld        %2d\n", first_vetor[i], second_vetor[i]);
    }
}   