#include <stdio.h>
#include <stdlib.h>

void fatorial(int num, int 1);

int main(void) {

    fatorial(5, 1);
    return 0;
}

void fatorial(int num, int i){
    int result;    

    if (num <= 1){
        printf("%d", result);
        return;
    }

    i *= (num - 1);
    
    printf("%d ", i);
    fatorial(num - 1, i);
}