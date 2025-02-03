// Falta fazer sistema de verificar player ganhador.

#include <stdio.h>
#define DIM 3
#define SPACE ' '

void defineInitMarks(char mark_loc[DIM][DIM]);
void drawTable(char table_marks[DIM][DIM]);

int main(void){
    char game[DIM][DIM];
    char ch = 'O';
    int posx, posy;
    int plays = 0;

    defineInitMarks(game);
    while (1){
        drawTable(game);
        printf("\nIntroduza linha e coluna desejadas: ");
        scanf("%d %d", &posy, &posx);

        posx--;
        posy--;

        if (game[posy][posx] == SPACE){
            game[posy][posx] = ch = (ch == 'O') ? 'X' : 'O';
            plays++;
        } else {
            printf("Ocupado\n Jogue novamente!\n");
        }

        if (plays == DIM * DIM){
            puts("Fim do jogo.");
            break;
        }
    }
    
}

void defineInitMarks(char mark_loc[DIM][DIM]){
    for (int i = 0; i < DIM; i++){
        for (int j = 0; j < DIM; j++){
            mark_loc[i][j] = SPACE;
        }
    }
}

    /* ************************************************************
    *   Criando lógica para construção do tabuleiro  onde que     *
    *   o tabuleiro será construido com base no mapeamento atual  *
    *   dos caracteres já digitados.                              *
    ************************************************************ */

void drawTable(char table_marks[DIM][DIM]){
    for (int i = 0; i < DIM; i++){ 
        for (int j = 0; j < DIM; j++){ 
            printf("%c %c", table_marks[i][j], j == DIM - 1? ' ': '|');
        } if (i != DIM - 1){
            printf("\n--------\n");
        }
    }
}
