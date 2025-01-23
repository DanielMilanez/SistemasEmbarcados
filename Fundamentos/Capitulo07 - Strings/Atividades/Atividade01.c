#include <stdio.h>

int main(void) {
    char pais[30];

    while (1){
        printf("Informe um nome de um pais: ");
        gets(pais);

        if (pais[0] == '\0'){
            break;

        } else {
            printf("Pais: %s\n\n", pais);
        }
    }
}
