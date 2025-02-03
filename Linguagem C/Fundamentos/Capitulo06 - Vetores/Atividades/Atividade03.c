 #include <stdio.h>
 #include <stdlib.h>
 #include <stdbool.h>

#define lines 4
#define colums 6

int main(void){
    int matriz[lines][colums] = {0};
    int num, userLine, userColum;
    char opt;

    while(true){
        system("CLS");

        for (int i = 0; i < lines; ++i){ 
            printf("------------------------------------\n");
            printf("|");
            for (int j = 0; j < colums; ++j){ 
                printf("%3d | ", matriz[i][j]);
            }
            printf("\n");
        }

        printf("------------------------------------\nInsira <n> para finalizar o programa\n\n");

        printf("Deseja continuar? ");
        scanf("%c", &opt);
        if (opt == 'n') break;
        fflush(stdin);
        printf("------------------\n");

        printf("Insira uma linha >> ");
        scanf("%d", &userLine);
        fflush(stdin);

        printf("Insira uma coluna >> ");
        scanf("%d", &userColum);
        fflush(stdin);

        printf("Insira um numero >> ");
        scanf("%d", &num);
        matriz[userLine - 1][userColum - 1] = num;
        fflush(stdin);

    }
}
