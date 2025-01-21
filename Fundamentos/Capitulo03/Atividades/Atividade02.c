#include <stdio.h>

int main(void){
    int firstOperando, secondOperando;
    scanf("%d %d", &firstOperando, &secondOperando);

    printf("A == B: %2d\n", firstOperando == secondOperando);
    printf("A  < B: %2d\n", firstOperando < secondOperando);
    printf("A  > B: %2d\n", firstOperando > secondOperando);
    printf("A <= B: %2d\n", firstOperando <= secondOperando);
    printf("A >= B: %2d\n", firstOperando >= secondOperando);
    printf("A != B: %2d\n", firstOperando != secondOperando);
}