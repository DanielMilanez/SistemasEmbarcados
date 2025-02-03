// Desenhando degraus
#include <stdio.h>
#include <locale.h>

int main(void) {
    setlocale(LC_ALL, "Portuguese_Brazil");
    unsigned short int degraus, 
                        count;

    printf("Informe o número de degraus que você deseja: ");
    scanf("%hu", &degraus);

    printf("==============================================");

    for (int i = 0; i < degraus; ++i){
        for (int j = 0; j < count; ++j){
            printf("#");
        }
        count++;
        printf("\n");
    }
    
    printf("==============================================");
}
