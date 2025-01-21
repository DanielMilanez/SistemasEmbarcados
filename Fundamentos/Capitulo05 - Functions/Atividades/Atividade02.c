#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void escreva(int num);

int main(void) {
    short int num;

    while (true) {
        printf("Informe um numero >> ");
        scanf("%hd", &num);
        fflush(stdin);

        if (num == 3) escreva(num);
        if (num == 7) escreva(num);
        if (!num) break;
    }
    
}

void escreva(int num) {
    switch (num) {
    case 3:
        printf("++++++++++++++++\n");
        printf("|              |\n");
        printf("| N U M E R O 3|\n");
        printf("|              |\n");
        printf("++++++++++++++++\n");
        break;
    
    case 7:
        printf("++++++++++++++++\n");
        printf("|              |\n");
        printf("| N U M E R O 7|\n");
        printf("|              |\n");
        printf("++++++++++++++++\n");
        break;
    }
}
