#include <stdio.h>
#include <stdlib.h>

int main(void) {

    char tmap[4][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}
    };


    putchar(tmap[0][0]);

    return 0;
}