// Criando uma função para verificar se uma string contem ou não um caractere.
#include <stdio.h>
#include <string.h>

int isNull(char *s); // Não é uma função padrão...

int main(void){
    printf("%d\n", isNull("")); // Retorna TRUE pois não possui caracteres
    printf("%d\n", isNull("Olá")); // Retorna FALSE pois possui caracteres
}

int isNull(char *s){
    return (s[0] == '\0'); // Verificando se o primeiro caractere é o delimitador.
    // return (strlen(s) == 0); Versão alternativa
}
