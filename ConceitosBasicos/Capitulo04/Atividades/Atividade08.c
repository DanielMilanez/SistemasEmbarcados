#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

void escreveMenu(void);

int main(void) {
    char opit, opitConfirm;
    char select;

    // Necessário defeinir o padrão para ISO 8859-1
    setlocale(LC_ALL, "Portuguese_Brazil");

    escreveMenu();
    while (true){
        printf("Opi??o: ");
        scanf("%c", &opit);
        fflush(stdin);

        switch (opit){
            case 's':
            case 'S':
                printf("Tem certeza? ");
                scanf("%c", &opitConfirm);

                if (opitConfirm == 's' || opitConfirm == 'S'){
                    printf("Saindo do sistema...");
                    return false;
                } else printf("Cancelando opera??o\n");
                break;

            case 'c':
            case 'C':
                printf("Consultar\n");
                printf("Selecione um cliente para ser consultado do sistema\n01 - Omir Lacerda\n02 - Juareswaldo\n03 - Takoku Navara\n04 - Jacinto Leite Aquino Rego\n");
                scanf("%c", &select);
                fflush(stdin);
                printf("Informa??es de %c\n", select);
                printf("cpf: 000000\nrg: 000000\nconta: 132456\n");
                printf("================================================\n");
                break;
            case 'd':
            case 'D':
                printf("Selecione um cliente para ser deletado do sistema\n01 - Omir Lacerda\n02 - Juareswaldo\n03 - Takoku Navara\n04 - Jacinto Leite Aquino Rego\n");
                printf("selecione: ");
                scanf("%c", &select);
                fflush(stdin);
                printf("Usu?rio do indice %c foi deletado com sucesso\n", select);
                printf("================================================\n");
                break;

            case 'n':
            case 'N':
                printf("Novo cliente\nInforma??es inseridas com sucesso\nInsira as novas informa??es deste novo cliente\ncpf: 000000\nrg: 000000\nconta: 132456\n");
                printf("================================================\n");
                break;

            case 'l':
            case 'L':
                printf("Listar clientes\n01 - Omir Lacerda\n02 - Juareswaldo\n03 - Takoku Navara\n04 - Jacinto Leite Aquino Rego\n");
                printf("================================================\n");
                break;

            default:
                printf("Entrada inv?lida");
                break;
        }
    }
}

void escreveMenu(void){
    system("cls");

    printf("\t\tSelecione uma opi??o\n");

    printf("\t\t====================\n");
    printf("\t\tN - para novo cliente\n");
    printf("\t\tC - para consultar clientes\n");
    printf("\t\tD - para deletar clientes\n");
    printf("\t\tL - para listar clientes\n");
    printf("\t\tS - para sair do sistema\n");
    printf("\t\t====================\n\n");
}
