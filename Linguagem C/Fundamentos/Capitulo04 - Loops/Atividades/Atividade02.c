// Fazer um programa que imprima a tabuada completa

#include <stdio.h>

int main(void){
    int n, num = 1;

    while (num <= 10){  
        while (n <= 10){
            printf("%2d X %2d = %2d\n", num, n, num * n);
            n += 1;
        }
        num ++;
        n = 1;
    } 
}
