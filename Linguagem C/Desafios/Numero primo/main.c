#include <stdio.h>
#include <stdlib.h>

void verify(int num);

int main(void) {
    int number = 0;

    do{
        printf("Informe um numero (0 - sair): ");
        scanf("%d", &number);
        number == 0 ? puts("Saindo... ") : verify(number);
    } while (number != 0);
}

void verify(int num){
    int count = 0;
    for (int i = 1; i <= num; ++i){
        if (num % i == 0) ++count; 
    } 
    count > 2 ? puts("N eh primo!") : puts("Eh primo!");
}