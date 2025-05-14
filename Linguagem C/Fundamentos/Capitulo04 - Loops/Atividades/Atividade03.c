#include <stdio.h>

int main(void){
    int ramos, count;

    printf("Informe a quantidade de ramos que vc deseja: ");
    scanf("%d", &ramos);

    for (int i = 1; i <= ramos; i++){
        for (int j = 0; j <= count; j++){
            printf("*");
        }
        count++;
        printf("\n");
    }
}
