#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char s[100],
         *palloc;

    printf("Enctre com a string > ");
    gets(s);
    palloc = (char *)malloc(strlen(s) + 1);

    if (palloc == NULL){
        puts("Memoria insuficiente\n");
    } else {
        strcpy(palloc, s);
        
        putchar(0x0A);
        printf(s);
        putchar(0x0A);
        printf(palloc);

        free(palloc);
    }

    return 0;
}