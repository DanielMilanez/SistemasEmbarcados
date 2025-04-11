/* É possível passar uma função como parametro para outra função

    Eu consigo utilizar um ponteiro para acessar funções, tendo em vista
    que as funções ocupam um espaço na memória do computador.

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DIM 9

// void func (int *v, int size);
int letters(char *str);
int strsize(char *str);

void trata_str(char *s, int (*func) (char *));

int main(void) {
    char s1[41] = "DreamByte Group";
    // int vector[DIM] = {0};
    // func(vector, DIM);
    // printf("%d\n", strsize(s1));
    // printf("%d\n", letters(s1));
    trata_str(s1, letters);
    trata_str(s1, strsize);
}

// void func (int *v, int size){
//     for (int i = 0; i < size; ++i){
//         printf("%d\n", v[i]);
//     }
// }

int strsize(char *str){
    int i;

    for (i = 0; str[i] != '\0'; ++i){
        ++i;
    }

    return i;
}

int letters(char *str){
    int letter = 0;
    
    for (int i = 0; str[i] != '\0'; ++i) {
        if (isalpha(str[i])) ++letter;
    }

    return letter;
}

void trata_str(char *s, int (*func) (char *)){
    printf("O resultado \x82: ");
    printf("%d\n", (* func) (s));
}