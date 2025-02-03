 #include <stdio.h>
 #include <stdlib.h>

 int main(void){
    int mat[3][4] = {0};

    mat[0][0] = 2;
    mat[1][0] = 10;
    mat[0][1] = 13;
    mat[1][1] = 11;

    mat[2][3] = mat[1][1] * mat[0][0]; // Operações aritimeticas 

    for (int i = 0; i < 3; ++i){ // percorre a linha
        printf("------------------------\n");
        printf("|");
        for (int j = 0; j < 4; ++j){ // percorre a coluna
            printf("%3d | ", mat[i][j]);
        }
        printf("\n");
    }
 }