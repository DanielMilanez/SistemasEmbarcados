#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 6  
#define STR_SIZE 20

int numClientes = DIM;

/*---------------------------------------------------------*/

void show_all();
int share(char *client_name);
void show_menu(int found);
void overvew(int found);
void pop(int found);

/*---------------------------------------------------------*/

typedef struct {
    char user[STR_SIZE];
    char password[STR_SIZE];
} clerk;

typedef struct {
    char name[STR_SIZE];
    int idade;
    int fidelity;
    
} client;

/*---------------------------------------------------------*/

clerk clerklist[DIM] = {
                            {"guto",  "123456"},
                            {"ana",   "abcdef"},
                            {"joao",  "qwerty"},
                            {"maria", "654321"},
                            {"paulo", "senha123"},
                            {"lara",  "passw0rd"}
                        };

client clientlist[DIM] = {
                            {"joel",     18, 1},
                            {"hugo",     32, 0},
                            {"sara",     20, 1},
                            {"fernando", 38, 1},
                            {"thiago",   14, 0},
                            {"italo",    16, 0}
                        };

/*---------------------------------------------------------*/


int share(char *client_name){
    system("cls");
    for (int i = 0; i <= DIM; ++i){
        if (strcmp(clientlist[i].name, client_name) == 0){
            puts("Cliente encontrado!");
            return i;
        }
    }
    printf("N foi possivel encontrar o cliente %s em nossos arquivos\n\n", client_name);
    return 0;
}

void show_menu(int found){
    unsigned short choice; 
    char client_name[STR_SIZE];

    system("cls");

    if (!found){
        puts("Acesso negado!");
        return;
    }

    puts("Acesso concedido!");
    do{        
        puts("-----------------------");
        puts("01 - Verificar cliente");
        puts("02 - Remover cliente");
        puts("03 - Cadastrar cliente");
        puts("04 - Mostrar clientes cadastrados");
        puts("05 - Sair");
        puts("-----------------------\n\n");

        printf(">> ");
        scanf("%hu", &choice);
        fflush(stdin);

        switch (choice){
            case 1:
                printf("Informe o nome do cliente: ");
                gets(client_name);
                overvew(share(client_name));
                break;
            
            case 2:
                printf("Informe o nome para deletar >> ");
                gets(client_name);
                pop(share(client_name));
                break;

            case 3:
                if (numClientes < DIM) {
                        printf("Informe o nome >> ");
                        fgets(client_name, STR_SIZE, stdin);
                        client_name[strcspn(client_name, "\n")] = '\0';  

                        strcpy(clientlist[numClientes].name, client_name);

                        printf("Informe a idade >> ");
                        while (scanf("%d", &clientlist[numClientes].idade) != 1) {
                            printf("Entrada invalida. Digite um numero: ");
                            while (getchar() != '\n');  
                        }

                        printf("E fidelizado (1 = Sim, 0 = Não) >> ");
                        while (scanf("%d", &clientlist[numClientes].fidelity) != 1 || 
                            (clientlist[numClientes].fidelity != 0 && clientlist[numClientes].fidelity != 1)) {
                            printf("Entrada invalida. Digite 1 para Sim ou 0 para Nao: ");
                            while (getchar() != '\n');  
                        }

                        numClientes++;
                        printf("Cliente '%s' adicionado com sucesso!\n", client_name);
                    } else {
                        puts("Stack Overflow! Lista cheia.");
                    }

                    break;

            case 4:
                system("cls");
                show_all();
                break;
            case 5:
                puts("Saindo...");
            default:
                break;
        }
    } while(choice != 5);
}

void overvew(int found){
    if (!found){
        puts("Cliente n encontrado");
        return;

    } else {
        puts("Exibindo info. do cliente\n");
        printf("Nome: %s\n", clientlist[found].name);
        printf("Idade: %d\n", clientlist[found].idade);

        printf("Fidelizado: ");
        clientlist[found].fidelity != 0 ? printf("Sim") : printf("Nao");

        puts(" ");
        puts("-------------------------");
    }
}

void pop(int found){
    if (!found){
        puts("Cliente n encontrado");
        return;
    }

    for (int i = 0; i < numClientes; ++i){
        clientlist[found] = clientlist[found + 1];
    }

    numClientes--;
    puts("Cliente removido!");
}

void show_all(){
    puts("Lista de clientes");
    for (int i = 0; i < numClientes; ++i){
        printf("%s\n", clientlist[i].name);
    }
}
