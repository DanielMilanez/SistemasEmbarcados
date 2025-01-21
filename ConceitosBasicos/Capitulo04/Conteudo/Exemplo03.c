// Do While || Faça enquanto
#include <stdio.h>

int main(void){
    char op;

    do {
        printf("\tM E N U   P R I N C I P A L");
        printf("\n\n\t\t c - Clientes");
        printf("\n\n\t\t f - Fornecedores");
        printf("\n\n\t\t e - Encomedas");
        printf("\n\n\t\t s - Sair");
        puts("\n\t-----------------------------");
        printf("Op >> ");
        
        scanf(" %c", &op);
        fflush(stdin);

        switch (op){
            case 'c':
            case 'C':
                puts("vc escolheu CLIENTES!");
                break;
            case 'f':
            case 'F':
                puts("vc escolheu FORNECEDORES!");
                break;
            case 'e':
            case 'E':
                puts("vc escolheu ENCOMENDAS!");
                break;
        }
        getchar();
    } while (op != 's' && op != 'S');
}
