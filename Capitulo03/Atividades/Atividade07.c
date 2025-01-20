#include <stdio.h>

int main(void){
    float tensao;

    printf("Informe a tensao atual da bateria: ");
    scanf("%f", &tensao);

    tensao < 10 ? printf("ALERTA!\a") : printf("Tudo OK!");
}