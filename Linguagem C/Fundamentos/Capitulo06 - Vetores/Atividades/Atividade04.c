#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>

#define DIM 10

void menu();
void desenhaLinhas();
void desenhaMapa(char table[DIM][DIM]);

int main(void) {
    char table[DIM][DIM] = {0}, play;
    unsigned lineMark, columMark, erros = 0, pts = 0;

    system("cls");
    menu();

    printf("Podemos comecar? ");
    scanf("%c", &play);
    fflush(stdin);

    // Gerando posicionamento randomico dos barcos

    table[0][1] = 1;
    table[1][1] = 1;
    table[2][1] = 1;
    table[5][6] = 1;
    table[5][5] = 1;
    table[5][4] = 1;
    table[8][7] = 1;
    table[9][7] = 1;

    while (play == 's'){
        system("cls");
        menu();
        desenhaMapa(table);
        printf("\tALVOS ACERTADOS: %d   ||", pts);
        printf("    CHANCES PERDIDAS: %d\n\n", erros);

        if (pts >= 11){
            printf("\nVOCE DESTRUIU TODOS!\n\n");
            break;
        }

        if (erros == 10){
            printf("\n\a\a\a\aNOS PERDEMOS! VOCE VALHOU NA MISSAO!\n\n");
            break;
        }

        printf("Informe uma linha: ");
        scanf("%d", &lineMark);
        fflush(stdin);

        printf("Informe uma coluna: ");
        scanf("%d", &columMark);
        fflush(stdin);

        if (table[lineMark -1 ][columMark - 1] == 0){
            printf("\a\a\a");
            table[lineMark -1 ][columMark - 1] = 3;
            ++erros;
        }

        else { 
            printf("\a");
            table[lineMark -1 ][columMark - 1] = 2;
            ++pts;
        }
    }
}

void desenhaLinhas(){
    printf("\n\t\t   ");
    for (int i = 0; i < DIM; i++){
        printf("---");
    }
    printf("\n");
}

void desenhaMapa(char table[DIM][DIM]){
    // Numeração horizontal
    printf("\t\t  ");
    for (int i = 0; i < DIM; ++i) printf("%3d", i + 1);
    desenhaLinhas();

    // Numeração vertical | tabuleiro
    for (int i = 0; i < DIM; ++i){
        printf("\t\t%2d |", i + 1);

        for (int j = 0; j < DIM; ++j){
            if (table[i][j] == 2) {
                printf(" *|");
            }
            
            else if (table[i][j] == 3){
                printf(" @|");
            }
            else {
                printf("  |");
            }
        }
        desenhaLinhas();
    }
}

void menu(){
    printf("\t\t\t---------------------\n");
    printf("\t\t\t| BATALHA --- NAVAL |\n");
    printf("\t\t\t---------------------\n");
    printf("Regras: Destrua 8 barcos para ganhar, cada erro sera penalizado\n10 erros vc perde, tome cuidado!\n\n");
}
