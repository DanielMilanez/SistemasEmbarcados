#include <stdio.h>

int main(void){
    unsigned int dia, mes, ano;
    
    printf("DIA! MES! ANO!");
    printf("\n---------------------------\n");
    printf("Informe o ano o mes e o dia >> ");
    scanf("%d %d %d", &ano, &mes, &dia);
    printf("%d/%d/%d", dia, mes, ano);
}
