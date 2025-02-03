/* Este arquivo pertece ao exemplo 04 */
#include <stdio.h>
#include <stdlib.h>

extern int valor, numero, teste;

void resultado(){
    int soma;
    soma = valor + numero + teste;
    printf("Soma = %d\n", soma);
}
