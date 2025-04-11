#include <stdio.h>
#define len(arr) (int)(sizeof(arr) / sizeof((arr)[0])) // Lembre-se de fazer o casting

int main(void){
    int myVetor[100] = {0};
    printf("%d", len(myVetor));
}

// Isso também poderia ser implementado em uma função, sem falar que a utilização de macro é bem melhor