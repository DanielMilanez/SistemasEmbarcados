#include <stdio.h>
#include <stdlib.h>

int converterAD(int range);

int main(void){
    int range;

    printf("Insira um valor de 0 a 1023 >> ");
    scanf("%d", &range);
    printf("%d", converterAD(range));
}

int converterAD(int range){
    return range / (1024 / 256);
}