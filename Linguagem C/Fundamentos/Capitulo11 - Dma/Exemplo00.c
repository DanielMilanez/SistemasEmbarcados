/* Alocação dinamica de memória / estrutura de dados */
#include <stdio.h>

struct x
{
    int a;
    int b;
    int c;
};

int main(void)
{
    struct x meuNovoValor;

    int vetor[10];
    printf("Tamanho total em bytes da struct %u\n", sizeof(meuNovoValor));
    printf("Tamanho total de bytes do vetor %u\n", sizeof(vetor));
    printf("Tamanho do vetor em si: %u", sizeof(vetor) / sizeof(vetor[0]));
    return 0;
}
