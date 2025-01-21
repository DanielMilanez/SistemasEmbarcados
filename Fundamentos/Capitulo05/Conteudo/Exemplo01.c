#include <stdio.h>

void lineMaker(void){
    for (int i = 0; i <= 20; i++){
        putchar('*');
    }
    putchar('\n');
}

int main(void){
    putchar('\n');
    lineMaker();
    puts("Numeros de 1 a 5");
    lineMaker();

    for (int i; i <= 5; i++){
        printf("%d\n", i);
    }

    lineMaker();
}