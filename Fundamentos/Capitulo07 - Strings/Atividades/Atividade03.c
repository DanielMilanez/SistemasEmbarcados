// Cire um programa que contenha todas as funções de string
#include <stdio.h>
#include <stdlib.h>

// #include <ctype.h> para usar o isdigit
#include <string.h> // para usar as funções de string

int meuStrlen(char *str);
int meuStrvowel(char *str);
char *meuStrrev(char *str);
int meuIsdigit(char str);
int meuStrdigit (char *str);
int meuStrcmp(char *st1, char *st2);
char *meuStrcpy(char *dest, char *orig); // Função que retorna uma string
char *meuStrcat(char *orig, char *dest);

int main(void){
    char minhaString[20] = "Ola Mundo!";
    char stringTrocada[20];
    char stringDeConcat[20] = "Eu me chamo Daniel.";
    char strDigit[20] = "Daniel";

    printf("%d\n", meuStrlen(minhaString)); // Retorno esperado: 10
    printf("%d vogais\n", meuStrvowel(minhaString)); // Retorno esperado: 4 vogais

    meuStrcpy(stringTrocada, minhaString);
    printf("%s \n", stringTrocada); // Retorno: Ola Mundo!

    // Verifica se são iguais retornando um valor inteiro sendo ele v quando são diferentes ou f para iguais
    printf("%d \n", meuStrcmp(minhaString, stringTrocada));

    meuStrcat(minhaString, stringDeConcat); // Unindo duas strings
    printf("%s \n", minhaString); // Retorno esperado: Ola Mundo! Eu me chamo Daniel.

    meuStrrev(minhaString); // Inverte a string
    printf("%s\n", minhaString); // Resultado esperado: .leinaD omach em uE !odnuM alO

    printf("%d", meuStrdigit(strDigit));
}

int meuStrlen(char *str){
    int i = 0; 

    while (str[i] != '\0'){
        ++i;
    }

    return i;  
}

int meuStrvowel(char *str){
    int i = 0, vowel = 0;

    while (str[i] != '\0'){
        switch (str[i]){
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                vowel++;
                break;

            default:
                break;
        }
        ++i;
    }

    return vowel;
}

char *meuStrcpy(char *dest, char *orig){
    int i = 0;
    for (i = 0; orig[i] != '\0'; ++i){
            dest[i] = orig[i];
    }
    dest[i] = '\0'; // Transformando em uma string. Adicionando o delimitador.
    return dest;
}

char *meuStrcat(char *dest, char *orig) {
    int len = meuStrlen(dest);    
    int lenorig = meuStrlen(orig);

    for (int i = 0; i < lenorig; ++i) {
        dest[len + i] = orig[i]; 
    }

    dest[len + lenorig] = '\0'; 
    return dest;
}

char *meuStrrev(char *str){
    char aux;

    for (int i = 0, len = meuStrlen(str) - 1; i < len; i++, len--){
        aux = str[i];
        str[i] = str[len];
        str[len] = aux;
    }

    return str;
}

int meuStrcmp(char *st1, char *st2){
    int i = 0;
    for (i = 0; st1[i] == st2[i] && st1[i] != '\0'; ++i);

    return ((unsigned char) st1[i] - (unsigned char)st2[i]);
}

int meuStrdigit (char *str){
    int num = 0;

    for (int i = 0; str[i] != '\0'; ++i){
        if (meuIsdigit(str[i])) ++num;
    }

    return num;
}

int meuIsdigit(char str){
    return (str >= '0' && str <= '9');
}