#include <stdio.h>
#include <stdlib.h>

typedef struct {
    short dia,
          mes,
          ano;
} birthday;

typedef struct{
    char nome[30];
    char address[40];
    long phone;
    birthday b_date;
} people;

int main(void) {
    people guto = {"guto", "quadra 6", 999424148, {9, 1, 2005}};

    printf("Nome: %s\n", guto.nome);
    printf("End.: %s\n", guto.address);
    printf("Telefone: %ld\n", guto.phone);
    printf("Data de nasciemnto: %hd/%hd/%hd", guto.b_date.dia, guto.b_date.mes, guto.b_date.ano);

    return 0;
}