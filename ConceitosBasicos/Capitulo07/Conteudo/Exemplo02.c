// Funcionamento da função strlen da biblioteca <string.h>
#include <stdio.h>
#include <string.h>

int lenString(char *s);

int main(void){
    // Utilizando a função strlen para descobrir a quantidade de caracteres existentes há em uma string
    printf("%d\n", strlen("")); // Retorna 0
    printf("%d\n", strlen("Olá meu nome é Daniel")); // Retorna 23

    // Entretanto o funcionamento interno desta função é similar a função que criamos
    printf("%d - Usando função criada\n", lenString("Oi!")); // Retorna 3
    printf("%d\n", strlen("Oi!")); // Retorna 3
}

int lenString(char *s){
    int count = 0;

    while (s[count] != '\0') 
        count++;

    /* CODIGO ALTERNATIVO ***************************
    *   for (int count = 0; s[count] != '\0'; i++); *
    *   return count;                               *
    *********************************************** */

    return count;
}
