 // Pilha de memória. Um vetor que acumula dados 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LAYERS 8

void disp_piled(); // Mostra o conteudo atual da pilha
void push(int data_for_piled); // Adiciona um novo valor a pilha
int pop(); // Remove um valor da pilha

int *ptr1, // Primeiro ponteiro
    *ptr2, // Segundo ponteiro, minha ancora
     piled[LAYERS], // Minha pilha de informações
     count; // Variavel contadora para verificar a camada da pilha

int main(void) {
    int data_piled, choose;
    char out = 'n';
    
    ptr1 = piled;
    ptr2 = piled;

    while(true){
        puts("1 - mostrar pilha");
        puts("2 - inserir um dado");
        puts("3 - remover dado atual");
        puts("4 - sair");
        printf(">> ");
        scanf("%d", &choose);
        fflush(stdin);

        switch (choose){
            case 1:
                disp_piled();
                break;

            case 2:
                printf("Informe o dado a ser inserido >>");
                scanf("%d", &data_piled);
                push(data_piled);
                printf("Dado inserido com sucesso!\n\n");
                break;
            
            case 3:
                printf("Tem certeza <s> para confirmar <n> para desisitr --> ");
                out = getchar();
                fflush(stdin);

                if (out == 'n') break;
                else pop();
                break;
            case 4:
                puts("Saindo...");
                return 0;

            default:
                break;
        }

    }
}

void disp_piled(){
    system("cls");
    printf("\t\t|         |\n");
    for (int i = count; i != 0; --i){
        printf("\t\t   %4d   \n", piled[i]);
    }
    printf("\t\t|---------|\n");
}

void push(int data_for_piled){
    ++ptr1; // Apontando para 1 a mais, evitando a alteração na minha ancora

    if (ptr1 == (ptr2 + LAYERS)){
        printf("STACK OVERFLOW\n");
        system("PAUSE");
    }

    *ptr1 = data_for_piled;
    ++count;
}

int pop(){
    printf("Removido!\n\n");
    
    if (ptr1 == ptr2){
        printf("STACK EMPTY\n");
        return 0;
    }
    --count;
    --ptr1;

    return 1;
}
