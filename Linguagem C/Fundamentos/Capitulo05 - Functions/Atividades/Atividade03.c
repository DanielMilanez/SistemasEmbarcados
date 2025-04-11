#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

float frequency (float Ra, float Rb, float C);

int main(void) {
    float Ra, Rb, C;

    printf("Insira as informacoes Ra Rb e C: ");
    scanf("%f %f %f", &Ra, &Rb, &C);
    printf("freq = %.2fHz\n", frequency(Ra, Rb, C));
}

float frequency (float Ra, float Rb, float C){
    return 1.44 / ((Ra + 2 * Rb) * C);
}
