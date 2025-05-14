#include <stdio.h>
#include <stdlib.h>

#define DIM 1

void descriptografy(int vetor[]);

int main(void) {
    int bytes[DIM] = {0};

    system("cls");

    printf("\t\t===============\n");
    printf("\t\t|             |\n");
    printf("\t\t| CRIPTOGRAFY |\n");
    printf("\t\t|             |\n");
    printf("\t\t===============\n");

    printf("Informe o valor dos bytes iniciais sao %d bytes no total\n", DIM);
    printf("Lembre-se que os valores dos bytes estao em hexadecimal!!!\n\n");

    for (int i = 0; i < DIM; ++i){
        printf("%d -- ", i + 1);
        scanf("%x", &bytes[i]); // Salvando valores decimais
        fflush(stdin);
    }

    descriptografy(bytes);
}

void descriptografy(int vetor[]){
    printf("Incrementando em 5 os valores pares e subitraindo 3 dos impares.\n\n");

    for (int i = 0; i < DIM; i++){
        if (vetor[i] % 2){
            vetor[i] -= 3;
            printf("0x%X ", vetor[i]);
        } else {
            vetor[i] += 5;
            printf("0x%X ", vetor[i]);
        }
    }
    printf("\n\nDescriptografando valores!\n\n");

    for (int i = 0; i < DIM; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}
