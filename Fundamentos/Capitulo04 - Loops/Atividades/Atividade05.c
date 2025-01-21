// Calculando o fatorial de um determinado número.
#include <stdio.h>

int main(void){
    int numDigitado;
    int resultadoTotal = 1;

    printf("Digite um numero: ");
    scanf("%d", &numDigitado);

    printf("O fatorial de %d: ", numDigitado);
    for (int i = numDigitado; i > 0; i--){
        resultadoTotal *= i;
        printf("%d ", i);
    }

    printf("= %d", resultadoTotal);
}


/*O fatorial de um número é dado por uma multiplicação consecutiva do valor pelo valor anterior

    exemplo: 5!
    o resultado é a multiplicação de 5 * 4 * 3 * 2 * 1
*/