/* Calculo da média ponderada. Depois da aula dos vetores */
#include <stdio.h>
#include <stdlib.h>

#define DIM 3
#define calcula_media(nota1, nota2, nota3, peso1, peso2, peso3) \
        (((nota1 * peso1) + (nota2 * peso2) + (nota3 * peso3))  \
        / (peso1 + peso2 + peso3))

int main(void) {
    float med[DIM] = {0}; 
    float pes[DIM] = {0};

    float result;

    for (int i = 0; i < DIM; ++i){
        printf("Informe da %d nota >> ", i + 1);
        scanf("%f", &med[i]);
        fflush(stdin);
        
        printf("Informe o peso da %d nota >> ", i + 1);
        scanf("%f", &pes[i]);
        fflush(stdin);
    }

    result = calcula_media(med[0], med[1], med[2], pes[0], pes[1], pes[2]);
    printf("%.2f", result);
}
