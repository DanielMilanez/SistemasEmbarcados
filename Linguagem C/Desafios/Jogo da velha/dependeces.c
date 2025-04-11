#include <stdio.h>
#include <stdlib.h>

#define DIM 3

void drawMenu(){
    printf("\t\t\t\t---------------------\n");
    printf("\t\t\t\t| JOGO - DA - VELHA |\n");
    printf("\t\t\t\t---------------------\n");
    printf("Regras: Ganhe do seu oponente marcando 3 marcas iguais (X ou O) na horizontal vertical ou diargonal\ncrie estrategias para ganhar de seu oponente!\n\n");
}

void drawLinhas(){
    printf("\n\t\t\t\t   ");
    for (int i = 0; i < DIM; i++){
        printf("---");
    }
    printf("\n");
}

void draw(char table[DIM][DIM]){
    printf("\t\t\t\t  ");
    for (int i = 0; i < DIM; ++i) printf("%3d", i + 1);
    drawLinhas();

    for (int i = 0; i < DIM; ++i){
        printf("\t\t\t\t%2d |", i + 1);

        for (int j = 0; j < DIM; ++j){
            if (table[i][j] == 'X') {
                printf(" X|");
            } else if (table[i][j] == 'O'){
                printf(" O|");
            }
            else {
                printf("  |");
            }
        }
        drawLinhas();
    }
}

char ganhador(char table[DIM][DIM]) {
    for (int i = 0; i < 3; i++) {
        if (table[i][0] == table[i][1] && table[i][1] == table[i][2] && table[i][0] != 0) {
            printf("O jogador '%c' venceu!\n", table[i][0]);
            return table[i][0];
        }
    }

    for (int j = 0; j < 3; j++) {
        if (table[0][j] == table[1][j] && table[1][j] == table[2][j] && table[0][j] != 0) {
            printf("O jogador '%c' venceu!\n", table[0][j]);
            return table[0][j];
        }
    }

    if (table[0][0] == table[1][1] && table[1][1] == table[2][2] && table[0][0] != 0) {
        printf("O jogador '%c' venceu!\n", table[0][0]);
        return table[0][0];
    }

    if (table[0][2] == table[1][1] && table[1][1] == table[2][0] && table[0][2] != 0) {
        printf("O jogador '%c' venceu!\n", table[0][2]);
        return table[0][2];
    }

    int preenchidos = 1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (table[i][j] == 0) {
                preenchidos = 0;
                break;
            }
        }
        if (!preenchidos) break;
    }

    if (preenchidos) {
        printf("Empate!\n");
        return 'E'; 
    }
    return 0; 
}
