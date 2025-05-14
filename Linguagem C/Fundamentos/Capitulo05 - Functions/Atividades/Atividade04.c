#include <stdio.h>
#include <stdlib.h>

void calculoDeFrequencia(float R, float C, char select);

int main(void){
    float rValue,  
          cValue;

    char selection;

    printf("Entre com os valores de R e C >> ");
    scanf("%f %f", &rValue, &cValue);
    fflush(stdin);

    printf("Selecione uma das opt abaixo\nA - Calcular frequencia\nB - Calcular tempo\n");
    printf("Opt: ");
    scanf("%c", &selection);

    calculoDeFrequencia(rValue, cValue, selection);
    return 0;
}

void calculoDeFrequencia(float R, float C, char select) {
    float frequency, 
          time;

    if (select == 'A' || select == 'a'){
        frequency = 1 / (2 * 3.1415 * R * C);
        printf("Freq : %.2fHz", frequency);
    }
    else if (select == 'B' || select == 'b') {
        time = R * C;
        printf("Time = %.5fs", time);
    }
    else {
        printf("Entrada invalida, por favor insira valores adequados!");
    }
}
