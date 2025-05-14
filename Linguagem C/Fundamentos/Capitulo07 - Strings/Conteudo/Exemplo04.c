// String Copy - fazendo uma string ser atribuida a outra variável
#include <stdio.h>
#include <string.h>

char *strcpy(char *dest, char *orig){
    int i;

    for (i = 0; orig[i] != '\0'; i++)
        dest[i] = orig[i];
    
    /* Realizando a copia de traz para frente
        for (i = strlen(orig); i >= 0; i--){
            dest[i] = orig[i];
        return dest;
        }
    */

    dest[i] = '\0';
    return dest;
}