/*                          Aritimetica de ponteiros!             */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* Incrementando ou decrementando um ponteiro ele varia não de 1 em 1 mas sim o sizeof do tipo de dado.
    Ou seja o quanto que um dado ocupa em questão de espaço na memória do pc, o número de bytes ocupados. */

    int var = 10, *ptr_var = &var;

    printf("%p --> Escrevendo o valor utilizando o &var\n", &var);
    printf("%p --> Escrevendo o valor usando o ponteiro\n", ptr_var);

    ++ptr_var; // Acresendo o valor de "ptr_var" em sizeof o tipo de dado.
    printf("%p --> Incrementando em 1x usando o op unario ++: %d\n", ptr_var, (int)sizeof(var));
    
    --ptr_var; // Acresendo o valor de "ptr_var" em sizeof o tipo de dado.
    printf("%p --> Decrementando em 1x usando o op unario --: %d\n", ptr_var, (int)sizeof(var));

    ptr_var += 3; // Acressendo o valor de "ptr_var" em 3X o sizeof do tipo de dado.
    printf("%p --> Incrementando em 3x usando o op unario ++: %d\n", ptr_var, (int)sizeof(var));
}   