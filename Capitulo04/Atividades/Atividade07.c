#include <stdio.h>

int main(void){
    int firstValue, 
        secondValue;

    printf("Informe o valor do range: ");
    scanf("%d %d", &firstValue, &secondValue);

    while (firstValue <= secondValue){
        printf("%dHz\n\n", firstValue);
        firstValue ++; 
    } 
}