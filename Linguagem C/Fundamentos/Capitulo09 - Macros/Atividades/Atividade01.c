/*Sorteio de 10 números aleatórios com apenas 8bits*/

#include <stdio.h>
#include <stdlib.h>

#define  sorteia register int i; \
                 for(i = 0; i < 10; ++i) \
                 printf("%d\n", rand() / 128)

int main(void){
    sorteia;
}
