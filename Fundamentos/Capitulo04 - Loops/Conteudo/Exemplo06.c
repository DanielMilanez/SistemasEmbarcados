// É possível trabalhar com caracteres especiais utilizados na lingua portugesa
#include <stdio.h>
#include <locale.h>

int main(void) {
    setlocale(LC_ALL, "Portuguese_Brazil");
    
    float teste = 1.5;

    printf("Opições para a escrita, o único problema é a digitação de números com virgula, pois, com esta lib ele troca o . para uma ,");
    printf("Exemplo: %.2f", teste);
}