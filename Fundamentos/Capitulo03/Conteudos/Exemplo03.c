// Indentificar o estado civil de uma pessoa casado, solteiro, divorciado ou viuvo;
#include <stdio.h>

int main(void){
    char estado_civil;

    printf("Informe seu estado civil: ");
    estado_civil = getchar();

    switch (estado_civil) {
        case 'C':
            printf("Casado\n");
            break;

        case 'S':
            printf("Solteiro\n");
            break;

        case 'V':
            printf("Viuvo\n");
            break;

        case 'D':
            printf("Divorcido\n");
            break;

        default:
            printf("Estado civil invalido, digite um valido!\n");
            break;
    }
}
