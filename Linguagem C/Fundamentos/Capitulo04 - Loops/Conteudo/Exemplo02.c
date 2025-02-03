#include <stdio.h>

int main(void){
    int n = 10;

    while (n){ // Verifica se 'n' é falso ou não, lembrando que 0 é falso em C 
        printf("%d\n", n);
        n -= 1;
    }
}
