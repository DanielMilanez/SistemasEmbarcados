#include <stdio.h>

int main(void){
    unsigned int dia, mes, ano;
    
    printf("DIA! MES! ANO!");
    printf("\n---------------------------\n");
    printf("Informe o dia o mes e o ano >> ");
    scanf("%d %d %d", &dia, &mes, &ano);
    printf("%d/%d/%d", dia, mes, ano);
}
