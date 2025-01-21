#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    unsigned long i = 0;

    while (true) {
        if (kbhit()) break; // Funciona apenas em IDE's
        ++i;
        printf("%ld\n", i);
    }
}