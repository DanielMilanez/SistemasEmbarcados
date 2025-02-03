#include <stdio.h>

int main(void){
    int firstValue, secondValue;

    printf("Informe dois numeros: ");
    scanf("%d %d", &firstValue, &secondValue);

    printf("Os valores %d e %d ", firstValue, secondValue);

    if (firstValue == secondValue) printf("sao iguais!");
    else printf("sao diferentes!");
    
}