#include <stdio.h>

int main(void) {
    unsigned short *ptr_var, var;

    var = 5;
    ptr_var = &var;

    printf("%p\n", &var);
    printf("%p\n", ptr_var);
    printf("%p\n", &ptr_var); // Exibe o endereço de ptr, onde foi armazenado o ponteiro

    printf("%d\n", *ptr_var); // O mesmo que digitar var, ele aponta para o cónteudo do ponteiro, que este é o endereço de var, que vai resultar no valor de var
    printf("%d\n", var);

    // Atualizando o conteudo de forma indireta, aponto para o endereço da variável que está salvo no ponteiro "ptr_var"
    *ptr_var = 22;

    printf("%d\n", var);
}