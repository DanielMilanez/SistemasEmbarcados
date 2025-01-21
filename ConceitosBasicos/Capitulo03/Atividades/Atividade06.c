#include <stdio.h>

int main(void){
    float tensao, resistencia, corrente;
    short unsigned int select; 


    printf("Informe o valor de tensao e resistencia: ");
    scanf("%f %f", &tensao, &resistencia);

    printf("\t\t================");
    printf("\n01 - corrente que circula pelo resistor");
    printf("\n02 - potencia dissipada no resistor");
    printf("\n03 - valor da tensao para uma corrente de 100mA");
    printf("\n\t\t================");

    printf("\n\nselecione: ");
    fflush(stdin);
    scanf("%hu", &select);

    corrente = (float)tensao / resistencia;

    switch (select){
    case 1:
        printf("O valor da corrente e: %.2fA", corrente);
        break;
    case 2:
        printf("O valor da potencia dissipada e: %.2fW", (float)tensao * corrente);
        break;
    case 3:
        printf("O valor da tensao para uma corrente de 100mA e: %.2fV", 0.1 * resistencia);
    }
}
