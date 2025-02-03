#include <stdio.h>
#include <stdlib.h>

// Passando parametros pela linha de comando
int main(int argc, char *argv[]) {
    int num, quad;
    printf("num   quad\n");

    for (int i = 1; i < argc; ++i){
        num = atoi(argv[i]); // Converte a string para inteiro
        quad = num * num;
        printf("%2d %3d\n", num, quad);
    }
}
