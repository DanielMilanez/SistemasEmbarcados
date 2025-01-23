#include <stdio.h>

int main(void) {
    char nome[20], sobrenome[20], endereco[40], cidade[20], estado[20], cep[20],  telefone[10];

    printf("Informe seu nome \n");
    printf("Nome: ");
    gets(nome);

    printf("Sobrenome: ");
    gets(sobrenome);
    // gets(nome);

    printf("Informe seu endereco ");
    gets(endereco);

    printf("Informe sua cidade ");
    gets(cidade);
    
    printf("Informe seu estado ");
    gets(estado);

    printf("Informe seu CEP ");
    gets(cep);
    // gets(endereco);

    printf("Informe seu telefone: ");
    gets(telefone);

    printf("Nome >> %s \nEndereco >> %s\nCidade >> %s\nEstado >> %s\nCEP >> %s\nTelefone >> %s", nome, endereco, cidade, estado, cep, telefone);
}