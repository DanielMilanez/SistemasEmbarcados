// Função de troca.
#include <stdio.h>

void troca(int *firstValue, int *secondValue);

int main(void){
    int valorA, valorB;
    
    printf("Insira dois valores: ");
    scanf("%d %d", &valorA, &valorB); // Passando valores para serem salvos nos endereços de valorA e valorB
    
    printf("Antes da troca A = %d B = %d\n", valorA, valorB);
    troca(&valorA, &valorB); // Passando como parametro os endereços de A e B
    printf("Depois da troca A = %d B = %d\n", valorA, valorB);
}

// Alterando os valores das variáveis originais.
void troca(int *firstValue, int *secondValue){ // Recebendo os valores de A e B com ponteiros
    int temporaria;

    temporaria =  *firstValue; // Salvando valor de A em uma variável temporaria
    *firstValue = *secondValue; // Atualizando valor de A para o valor de B
    *secondValue = temporaria; // Atualizando o valor de B para o valor salvo em temporaria
}