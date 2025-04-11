// O objetivo deste desafio é verificar dois numeros,
// imagine que seja digitado dois numeros, A e B
// Caso A possua B em alguma parte digite 1, caso contrário digite 0
// 1024, 24 RESPOSTA: 1
// 1024, 1000 RESPOSTA: 0

#include <stdio.h>
#include <stdlib.h>

void verify(int num1, int num2);

int main(void) {
    verify(567890, 890);
    verify(1243, 1243);
    verify(2457, 245);
    verify(457, 2457);
    verify(5123, 23);
    printf("\n-----------------------\n\n");

    return 0;
}

void verify(int num1, int num2){
    int potencia = 1;
    int temp = num2;

    printf("\n-----------------------");
    printf("\n%d -- %d: ", num1, num2);
    while (temp > 0) {
        potencia *= 10;
        temp /= 10;
    }

    if (num1 % potencia == num2) printf("\t1");
    else printf("\t0");
}