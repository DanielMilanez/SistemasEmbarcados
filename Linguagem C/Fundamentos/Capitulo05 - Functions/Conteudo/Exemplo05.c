#include <stdio.h>
#include <stdlib.h>

// mult_dobro(int x, int y);
void quad_cube(int *a, int *b);

int main(void) {
    int x = 0, y = 0;

    printf("Valor de X: ");
    scanf("%d", &x);
    while (getchar() != '\n');

    printf("Valor de Y: ");
    scanf("%d", &y);
    while (getchar() != '\n');

    quad_cube(&x, &y);

    printf("O quadrado de x: %d\n", x);
    printf("O cubo de y: %d\n", y);

    // printf("(2x%d) X (2x%d) = %d\n", x,y, mult_dobro(x, y));
}

// mult_dobro(int a, int b){
//     a *= 2;
//     b *= 2;

//     return a * b;
// }

void quad_cube(int *a, int *b){
    // *a = (*a) * (*a);
    // *b = (*b) * (*b) * (*b);

    int tempA = *a,
        tempB = *b;

    *a = tempA * tempA;
    *b = tempB * tempB * tempB;  
}
