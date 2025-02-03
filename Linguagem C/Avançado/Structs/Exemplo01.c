#include <stdio.h>
#include <stdlib.h>

struct cliente {
    char name[30];
    char address[40];
    char city[30];
    char phone[11];
    int cep;

}info, dados;

int main(void) {
    info.cep = 123456;
    dados.cep = 12;
    
    printf("%d\n", info.cep);
    printf("%d\n", dados.cep);
}

