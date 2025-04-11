#include <stdio.h>

int main(void){
    int firstNumber, secondNumber;
    printf("Digite dois numeros: ");
    scanf("%d%d", &firstNumber, &secondNumber);

    printf("O resultado de %d + %d = %d\n", firstNumber, secondNumber, firstNumber + secondNumber);
}