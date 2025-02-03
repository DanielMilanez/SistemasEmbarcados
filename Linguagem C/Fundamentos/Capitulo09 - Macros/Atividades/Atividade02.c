/* Calculo da média ponderada. Devo fazer o código sem usar vetores */
#include <stdio.h>
#include <stdlib.h>

#define calcula_media(nota1, nota2, nota3, peso1, peso2, peso3)  \
                    (((nota1 * peso1) + (nota2 * peso2) +(nota3 * peso3)) \
                    / (peso1 + peso2 + peso3))

int main(void) {
    int i = 1;
    float result,
          nota1, 
          nota2, 
          nota3,
          peso1,
          peso2,
          peso3;


    printf("Nota%d ", i);
    scanf("%f", &nota1);
    fflush(stdin);

    printf("Peso%d ", i);
    scanf("%f", &peso1);
    fflush(stdin);

    ++i;
    printf("Nota%d ", i);
    scanf("%f", &nota2);
    fflush(stdin);

    printf("Nota%d ", i);
    scanf("%f", &peso2);
    fflush(stdin);

    ++i;
    printf("Nota%d ", i);
    scanf("%f", &nota3);
    fflush(stdin);

    printf("Peso%d ", i);
    scanf("%f", &peso3);
    fflush(stdin);

    result = calcula_media(nota1, nota2, nota3, peso1, peso2, peso3);
    printf("%.2f", result);
}