#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void caracteres(char novo_caractere, int repeat);

int main(void){
    char ch;
    short int num;

    while (true){
        printf("Digite um caractere para ser desenhado em numeros especiais >> ");
        scanf("%c", &ch);
        fflush(stdin);

        system("cls");

        printf("Numeros especiais: \n 0 - Sair \n 1 - Escreve o caractere na tela 10 vezes \n 3 - Escreve # tres vezes\n");
        printf("Digite um numero >> ");
        scanf("%hd", &num);
        fflush(stdin);
        
        if (!num) break;

        caracteres(ch, num);  
        system("cls");
    }

    return 0;
}

void caracteres(char novo_caractere, int choose){
    switch (choose){
        case 1:      
            for (int i = 0; i < 10; ++i){
                printf("%c", novo_caractere);
            }
            putchar('\n');
        break;
        
        case 3:
            for (int i = 0; i < 3; ++i){
                putchar('#');
            }
            putchar('\n');
        break;
    }

    printf("Precione <ENTER> para continuar");
    getchar();
}
