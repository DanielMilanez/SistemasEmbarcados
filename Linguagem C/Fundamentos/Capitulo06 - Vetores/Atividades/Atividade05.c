// Programa Boubble sort - Ordenação simples de vetores
#include <stdio.h>
#include <stdbool.h>
#define DIM 5

int main(void){
    int meuVetor[DIM];
    int meuValor = 0;
    int repeat = 0;

    int i = 1;

    for (i = 0; i < DIM; i++){
        printf("Insira o %d valor: ", i + 1);
        scanf("%d", &meuValor);

        meuVetor[i] = meuValor;
    }
    
    while (true){ 
        int trocou = 0; // Verifica se há trocas na operação

        for (i = 0; i < DIM - 1; i++){
            if (meuVetor[i] > meuVetor[i + 1]) {
                int temporaria = meuVetor[i];

                meuVetor[i] = meuVetor[i + 1];
                meuVetor[i + 1] = temporaria;

                trocou = true; 
                repeat++;
            } 
        }

        if (!trocou) break; // Caso não haja ele se mata.
    }

    printf("Vetor atualizado! Houve %d repeticoes\n", repeat);
    
    for (i = 0; i < DIM; i++){
        printf("%d ", meuVetor[i]);
    }
}

/*  
    Posso melhorar ainda mais este código adicionando a funcionalidade de alocação dinamica de memória
    neste caso, eu consigo definir o tamanho do vetor que eu vou analizar. Futuramente devo estudar 
    mais a respeito para melhorar este algoritmo.
*/