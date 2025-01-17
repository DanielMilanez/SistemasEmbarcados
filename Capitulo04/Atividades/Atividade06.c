// Verificar se um determinado número é primo ou não
#include <stdio.h>

int main(void){
    int number;
    int count;

    printf("Digite um numero primo >> ");
    scanf("%d", &number);

    for (int i = 1; i < number; i++) {
        if (number % i == 0){
            count++;
        }
    } 

    if (count < 2){
        printf("E primo!");
    } else {
        printf("N e primo!");
    }

}