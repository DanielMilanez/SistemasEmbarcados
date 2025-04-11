// Escreva um programa que calcule o perimetro de um circulo
#include <stdio.h>

int main(void){
    float raio, perimetro;
    double pi = 3.1415927, area;

    printf("Informe o valor do raio da circunferencia >> ");
    scanf("%f", &raio);
    area = pi * raio * raio;
    perimetro = 2 * pi * raio;

    printf("Area = %f\nPerimetro = %f\n", area, perimetro);
}