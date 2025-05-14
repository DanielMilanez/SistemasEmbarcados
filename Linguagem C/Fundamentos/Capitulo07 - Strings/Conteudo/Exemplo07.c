#include <stdio.h>

int main(void){
    /* Utilizando o scanf torna-se necessário a utilização de mais de uma variável
       pois ele atribui o delimitador quando vê um espaço*/
    char nome[20], sobrenome[20], newNome[20];

    printf("Informe seu nome: ");
    scanf("%s %s", nome, sobrenome);
    fflush(stdin);

    printf("Informe seu nome: ");
    gets(newNome);
    fflush(stdin);

    printf("\nNome: %s %s separado em duas variaveis distintas, o valor do nome completo e perdido, limitando-se apenas a dois nomes\nn estou usando o gets \n\n", nome, sobrenome);
    printf("Nome: %s separado em uma unica variavel, estou usando o gets, o valor nome completo n e perdido \n\n", newNome);
}