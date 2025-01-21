#include <stdio.h>
// #define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

int len(int vetor[]);

int main(void){
    int myVetor[100] = {0};
    
   printf("%d", len(myVetor));
}

int len(int vetor[]){
    int condicional =  sizeof(vetor) / sizeof(vetor[0]);
    return condicional;
}
