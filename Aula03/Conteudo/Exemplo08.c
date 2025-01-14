#include <stdio.h>

int main(void){
    char ch, confirm;
    int asciiValue;

    printf("\n\nDescobrindo o valor respectivo em ASCII de um caractere!");
    printf("\n--------------------------\n");

    printf("Introduza um caractere: ");
    ch = getchar();

    printf("O caractere %c em ASCII e: %d", ch, (int)ch); // Utilizando casting para passar como parametro um valor inteiro
    printf("\n--------------------------\n");

    printf("Deseja testar? ");
    fflush(stdin);
    scanf("%c", &confirm);

    if (confirm == 's'){
        printf("Introduza o numero do caractere em ASCII: ");
        scanf("%d", &asciiValue);    

        printf("O valor %d em ASCII significa: %c", asciiValue, (char)asciiValue);
        printf("\n--------------------------\n");

        printf("O caractere anterior ao %d e: '%c' (%d)\n", asciiValue, (char)(asciiValue - 1), asciiValue - 1);
        printf("O caractere sucessor ao %d e: '%c' (%d)", asciiValue, (char)(asciiValue + 1), asciiValue + 1);
    }
    
    printf("\n--------------------------\n");
    printf("Fim do programa...\n"); 
}
