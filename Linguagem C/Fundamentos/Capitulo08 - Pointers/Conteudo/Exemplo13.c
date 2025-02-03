#include <stdio.h>
#include <stdlib.h>

int main(void) {
    float a = 12.4, b = 78.2;
    float *ptra, *ptrb;

    float **geral;

    ptra = &a;
    ptrb = &b;

    geral = &ptra;

    printf("%p\n", &ptra);
    printf("%f\n", **geral);

    --geral;
    printf("%p\n", &ptrb);
    printf("%f\n", **geral);
}