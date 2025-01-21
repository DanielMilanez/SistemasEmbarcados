#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

int main(void) {
    setlocale(LC_ALL, "Portuguese_Brazil");

    unsigned short int num;
    
    while (true){
        printf("Insira um número: ");
        scanf("%hd", &num);
        fflush(stdin);

        if (num  % 2) break;
        printf("Tudo OK\n");
    }

    printf("Erro....");
}
