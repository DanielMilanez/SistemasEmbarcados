/*É possível trabalhar com tipos de dados distintos com uma mesma macro*/
#include <stdio.h>
#include <stdlib.h>

#define div(a, b) a / b

int main(void){
    int resultado_int;
    float resultado_f;

    resultado_int = div(10, 5);
    resultado_f = div(123.47, 27.8);

    printf("%d\n", resultado_int);
    printf("%f\n", resultado_f);

}