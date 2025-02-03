#include <stdio.h>
#include <stdlib.h>

#define DIM 5

int main(void) {
    float maxValue, subTotal;
    float aports[DIM] = {0}; 
    int qnt[DIM] = {0}; 
    char opt = 's';

    do{
        printf("Valor do aporte que sera executado >> R$");
        scanf("%f", &maxValue);
        fflush(stdin);

        for (int i = 0; i < DIM; ++i){
            printf("EMP%c%d: R$", (char)(i + 65), i + 2);
            scanf("%f", &aports[i]);
            fflush(stdin);

            printf("Qtd.: ");
            scanf("%d", &qnt[i]);
            fflush(stdin);

            subTotal += aports[i] * qnt[i];
            printf("\n");
        }

        subTotal > maxValue ? printf("\aO valor do maximo do aport e inferior ao valor que \
        vc deseja aportar\nValor total: R$%.2f\n", subTotal) : printf("Valor aportado! Total \
        >> R$%.2f\n", subTotal);

        printf("Calcular novamente?\n <s> sim | <n> nao >>");
        scanf("%c", &opt);
        fflush(stdin);  

    } while (opt == 's');
    system("PAUSE");
}
