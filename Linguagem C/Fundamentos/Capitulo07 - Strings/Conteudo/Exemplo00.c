#include <stdio.h>

// void concatenarStrings (char string1[], int t1, char string2[], int t2, char string3[]);
// int tamanhoString(char string[]);
// int stringsIguais(char s1[], char s2[]);   

int main(void){
/************************************************************************************************/

    // // char palavra1[] = {'p','a','o',' '};
    // // char palavra2[] = {'m','o','r','t','a','d','e','l','a'};
    // char palavra1[] = "Pao ";
    // char palavra2[] = "mortadela";

    // char novaPalavra[13];

    // concatenarStrings(palavra1, 4, palavra2, 9, novaPalavra);

    // for (int i = 0; i < 13; i++){
    //     printf("%c", novaPalavra[i]);
    // }

/************************************************************************************************/

    // char stringUser[20];

    // printf("Digite uma palavra: ");
    // scanf("%s", stringUser);

    // int num = tamanhoString(stringUser);
    // printf("A string %s possui %d caracteres", stringUser, num);

/************************************************************************************************/

    // char stringUser1[20], stringUser2[20];

    // printf("Digite uma palavra: ");
    // scanf("%s", stringUser1);

    // printf("Digite outra palavra: ");
    // scanf("%s", stringUser2);

    // if (stringsIguais(stringUser1, stringUser2)) {
    //     printf("%s e %s sao iguais\n", stringUser1, stringUser2);
    // } else {
    //     printf("%s e %s nao sao iguais\n", stringUser1, stringUser2);
    // }

/************************************************************************************************/
}

// Concatenação de strings.
// void concatenarStrings (char string1[], int t1, char string2[], int t2, char string3[]){
//     for (int i = 0; i < t1; i++){
//         string3[i] = string1[i];
//     }
//     for (int j = 0; j < t2; j++){
//         string3[t1 + j] = string2[j]; 
//     }
// }

// Contar caracteres de uma string.
// int tamanhoString(char string[]){
//     int numCaracteres = 0;
    
//     // O caractere núlo ocupa a última posição da minha string
//     while(string[numCaracteres] != '\0'){
//         numCaracteres++;
//     } numCaracteres++; // Considerando o último caractere '\0'

//     return numCaracteres;
// }

// Verificar igualdede entre duas strings
// int stringsIguais(char s1[], char s2[]){
//     int i = 0;
//     while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0') i++;

//     if(s1[i] == '\0' && s2[i] == '\0'){
//         return 1;
//     }   else {
//         return 0;
//     }
// }