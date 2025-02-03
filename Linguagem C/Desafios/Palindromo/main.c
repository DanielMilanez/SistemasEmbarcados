#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void ispalindrome(char *word);
int len(char *word);

int main(void) {
    char word[40];

    puts("Verificador de palindromos!");
    puts("--------------------------\n");
    printf("Insira uma palavra ou numero >> ");
    gets(word);
    
    printf("O que foi digitado %s ha %d caracteres\n\n", word, len(word));
    printf("O que foi digitado ");
    ispalindrome(word);
    puts("--------------------------\n");


    return 0;
}

void ispalindrome(char *word){
    int i = 0, j = 0;

    for (i = 0, j = len(word) - 1; i < j; ++i, --j){
        if (word[i] != word[j]){
            printf("nao eh palindromo!\n\n");
            return;
        }
    }

    printf("eh palindromo\n\n");
}

int len(char *word){
    int i = 0;
    for (i = 0; word[i] != '\0'; ++i);
    return i;
}