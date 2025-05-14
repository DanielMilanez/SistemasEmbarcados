#include <stdio.h>
#include <stdlib.h> 

int main(void) {
    int A = 100, *B, **C;
    B = &A;

    // C = &A; Erro lógico, C dev apontar para um ponteiro
    C = &B;

    printf("End. de A: %p\t Cont. de A: %d\n", &A, A);

    printf("End. de B: %p\t Cont. de B: %d\n", &B, *B);
    printf("Cont. apontado por B: %d\n", *B);

    printf("End. de C: %p\t Cont. de C: %p\n", &C, C);
    printf("Cont. apontado por C: %d\n", **C);

    return 0;
}