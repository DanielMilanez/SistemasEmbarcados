// Incremento e decremento
#include <stdio.h>
#include <stdlib.h>

int main(void){
    int xvalue,
        yvalue;
    
    xvalue = 5;
    yvalue = 8;

    system("cls");

    printf("Antes de atribuir\n");
    printf("X = %d\n", xvalue);
    printf("Y = %d\n", yvalue);

    printf("Realizando op.\n");
    printf("Precione <ENTER> para continuar...");
    getchar();
    

    printf("Resultado de quando primeiro incrementamos e dps atribuimos: \n");
    yvalue = ++xvalue;

    printf("X = %d\n", xvalue);
    printf("Y = %d\n", yvalue);

    yvalue = 8;
    printf("Resultado de quando atribuimos e dps incrementamos: \n");
    printf("Considere os valores anteriores.\n");

    yvalue = xvalue++;

    printf("X = %d\n", xvalue);
    printf("Y = %d\n", yvalue);


}