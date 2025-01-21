#include <stdio.h>

int main(void){
    short int minutos = 0;
    float horas = 0.0;

    printf("Insira os minutos para a conversao: ");
    scanf("%hd", &minutos);

    horas = (float) minutos / 60.0;
    printf("\n%d min --> %.2fhrs ", minutos, horas);
}