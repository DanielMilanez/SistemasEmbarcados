#include <stdio.h>
#include <stdlib.h>

enum carros{
    ford,
    honda,
    volks = 50,
    renault
} conc;

int main(void) {    
    printf("%d\n", conc);
    printf("%d\n", ford);
    printf("%d\n", honda);
    printf("%d\n", volks);
    printf("%d\n", renault);

    return 0;
}