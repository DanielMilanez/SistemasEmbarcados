#include <stdio.h>
#include <stdlib.h>

int strcount(const char *s);

int main(void) {
    printf("O tamanho da variavel my_string eh %d ", strcount("Teste muito bacanudo de string"));
}

int strcount(const char *s){
    if (*s == '\0') return 0;
    else return 1 + strcount(s + 1);
}