#include <stdio.h>

// Criando um prótotipo
void linha(int num); // Demonstra para o compilador o tipo de retorno da função
/*O compilador se desvia do seu fluxo de resolução natural, declara esses pré processos e retrona para o flxo original*/
int main(void){
    linha(3);
    linha(5);
    linha(7);
    linha(5);
    linha(3);
}

void linha(int num){
    for (int i = 0; i <= num; i++){
        putchar('*');
    }
    putchar('\n');
}
