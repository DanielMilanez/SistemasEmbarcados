#include <stdio.h>

int main(void){
    int num1, num2;
    char operation;

    printf("Escreva uma exprecao >> ");
    scanf("%d %c %d", &num1, &operation, &num2); // NÃO ESQUECER DOS ELOS!

    switch (operation){
        case '*':
        case 'X':
        case 'x':
            printf("%d X %d = %d\n", num1, num2, num1 * num2);
            break;

        case '+':
            printf("%d + %d = %d\n", num1, num2, num1 + num2);
            break;

        case '-':
            printf("%d - %d = %d\n", num1, num2, num1 - num2);
            break;
        
        case '/':
        case ':':
        case '\\': // Caractere especial, necessário outra barra para representar o "\"
            printf("%d : %d = %d\n", num1, num2, num1 / num2);
            break;
        
        default:
            printf("Entrada invalida");
            break;
    }
}
