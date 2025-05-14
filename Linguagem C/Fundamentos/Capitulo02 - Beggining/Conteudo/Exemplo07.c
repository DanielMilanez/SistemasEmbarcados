#include <stdio.h>

int main(void){
    char ch1, ch2;

    printf("Introduza um caractere: ");
    scanf("%c", &ch1);

    // fflush(stdin);
    printf("Informe outro caractere: ");
    // scanf(" %c", &ch2);
    scanf("%c", &ch2); // Erro ocasionado pelo buffer (memória temporaria que amareza os dados de entrada do teclado)

    /*Algo que em linguagens de mais alto nivel não era relevante, pois, isso era feito de forma automatica o curioso é
    que agora precisamos nos preocupar com a memória temporaria que está presente no nosso teclado!*/

    printf("Os caracteres introduzidos foram '%c' e '%c'\n", ch1, ch2);
}