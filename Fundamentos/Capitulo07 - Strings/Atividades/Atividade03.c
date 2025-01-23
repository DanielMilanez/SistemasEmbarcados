// Cire um programa que contenha todas as funções de string
#include <stdio.h>

int meuStrlen(char *str);
int meuStrvowel(char *str);
char *meuStrcpy(char *dest, char *orig);
char *meuStrcat(char *orig, char *dest);

int main(void){
    char minhaString[20] = "Ola Mundo!";
    char stringTrocada[20];
    char stringDeConcat[20] = "Eu me chamo Daniel.";

    printf("%d\n", meuStrlen(minhaString)); // Retorno esperado: 10
    printf("%d vogais\n", meuStrvowel(minhaString)); // Retorno esperado: 4 vogais

    meuStrcpy(stringTrocada, minhaString);
    printf("%s \n", stringTrocada); // Retorno: Ola Mundo!

    meuStrcat(minhaString, stringDeConcat); // Unindo duas strings
    printf("%s \n", minhaString); // Retorno esperado: Ola Mundo! Eu me chamo Daniel.

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
