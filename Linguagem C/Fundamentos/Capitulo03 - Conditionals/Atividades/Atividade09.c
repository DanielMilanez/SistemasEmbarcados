#include <stdio.h>

int main(void){
    int num1,
        num2,
        num3,
        num4,
        soma;

    printf("Insira 4 numeros inteiros positivos: ");
    scanf("%d %d %d %d", &num1, &num2, &num3, &num4);

    // Soma parcial de todos os numeros
    soma = num1 + num2 + num3 + num4;

    num4 = num3 + (--num2);
    num3 = num1++;

    printf("O resultado atual de cada um dos numeros e\n\n num1 = %d \n num2 = %d \n num3 = %d \n num4 = %d \n\n", num1, num2, num3, num4);

    // Soma de todos os numeros envolvidos no processo
    soma += num1 + num2 + num3 + num4;
    printf("A soma eh: %d", soma);

}