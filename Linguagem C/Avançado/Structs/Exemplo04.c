#include <stdio.h>
#include <stdlib.h>

union teste {
    short val1;
    char val2;
} valor;

int main(void) {
    valor.val1 = 100;
    valor.val2 = 'A';

    printf("%hd\n", valor.val1);
    printf("%c\n\n\n", valor.val2);

    valor.val2 = 'A';
    valor.val1 = 100;

    printf("%hd\n", valor.val1);
    printf("%c\n", valor.val2);

    return 0;
}
