/* Criar um programa que realize a leitura dos salarios pagos a um individuo durante um ano
em seguida, o programa deverá mostrar os valores mensais e o total anual.*/
#include <stdio.h>

int main(void){
    float salario[12], total; // Salvando os 12 meses
    
    for (int i = 1; i <= 12; i++){
        printf("Digite o salario do mes %d R$", i);
        scanf("%f", &salario[i - 1]); // Não esqueça do elo
    } 

    // Aqui as informações já estão salvas no vetor.
    // Exibindo o valor total
    puts("\tMes\t\t   Valor");
    for (int i = 1; i <= 12; i++){
        printf("\t %3d\t\t%9.2f\n", i, salario[i-1]);
        total += salario[i];
    }
    printf("Total anual: R$%9.2f", total);
}
