#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dependeces.c"

#define DIM 3

int main(void){
    char table[DIM][DIM] = {0};
    char winner = ' ';
    unsigned line, colum;
    int mark = 0;

    while (true){
        mark = 0;
        system("cls");
        drawMenu();
        draw(table);

        do{
            printf("Jogador X\n");
            printf("Escreva a linha e a coluna desejada: ");
            scanf("%d %d", &line, &colum);
            fflush(stdin);

            if (table[line - 1][colum - 1] == 0) {
                table[line - 1][colum - 1] = 'X';
            }
            else {
                printf("Linha ja ocupada, esolha outra!\n"); 
                continue;
            }

            system("cls");
            drawMenu();
            draw(table);
            winner = ganhador(table);
            if (winner != 0) break;

            printf("Jogador O\n");
            printf("Escreva a linha e a coluna desejada: ");
            scanf("%d %d", &line, &colum);
            fflush(stdin);

            if (table[line - 1][colum - 1] == 0) {
                table[line - 1][colum - 1] = 'O';
            }
            else {
                printf("Linha ja ocupada, esolha outra!\n"); 
                continue;
            }

            system("cls");
            drawMenu();
            draw(table);
            winner = ganhador(table);
            if (winner != 0) break;

            mark = 1;
        } while (mark == 0);
    }
}
