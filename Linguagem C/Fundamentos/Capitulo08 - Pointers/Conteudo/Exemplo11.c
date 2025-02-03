#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void) {
    int var = 15;
    int *ptr_var = &var;
    int **ptr_ptr = &ptr_var;
    
    printf("Valor de var %d\n", var);
    printf("Valor de ptr_var %d\n", *ptr_var);
    printf("Valor de ptr_ptr %d\n", **ptr_ptr);

    /* Modificando o conteudo de var*/
    **ptr_ptr = 123;

    printf("\nValor de var %d\n", var);
    printf("Valor de ptr_var %d\n", *ptr_var);
    printf("Valor de ptr_ptr %d\n", **ptr_ptr);

}