#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Comparação de ponteiros

    int *ptr_a, *ptr_b;
    int a, b; // Alterando a ordem de declaração modifica o valor de seu endereço. Ele se altera

    a = 10;
    b = 30;

    ptr_a = &a;
    ptr_b = &b;

    printf("a addr: %p\n", &a);
    printf("b addr: %p\n", &b);

    if (ptr_a > ptr_b) printf("The addrress of a is bigger\n");
    else printf("The addrress of b is bigger\n");

}   