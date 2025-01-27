// Ponteiros e vetores
#include <stdio.h>
#include <stdlib.h>

int main(void){
    int vetor[10] = {2, 4, 5, 6};
    int *pont_vetor = vetor; // Recebe o ponteiro constante.

    printf("%p\n", vetor); // Mostra o endereço de memória do primeiro elemento do vetor
    // O nome do vetor é um ponteiro constante!

    // Informando o indice, eu imprimo o valor
    printf("%d\n", vetor[0]); // Mostra o conteudo. Do indice 1.
    /*
        Curioso, o nome do vetor referencia o primeiro indice e o espaço alocado na memória por ele
        agora quando referenciamos um indice especifico ele imprime o conteudo desse indice
        
        Eles vão ter 4 bytes de diferença um do outro, então considere um espaço

        Memória, como pode ver, ela altera avança 4 em 4 pois o tipo de dado é do tipo int e ocupa 4 bytes uma
        unidade.

        ..0 ..4 ..8 ..12   ...
        | 2 | 1 | 2 |  3 | ... | 9 |
    */

    printf("%p\n", pont_vetor);
    printf("%d\n", *pont_vetor); // Acessando o conteudo.
    printf("%p\n", &vetor[1]); // Mostra o endereço de memória do primeiro elemento do vetor
    printf("%d\n", vetor[1]); 


    // Somando um número no nosso ponteiro vamos "andar" para o próximo indice do vetor
    *(pont_vetor + 1) = 30;
    printf("%d\n", pont_vetor[1]);
    printf("%d\n", pont_vetor[2]);
    printf("%d\n", pont_vetor[3]);
}