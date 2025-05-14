#include <stdio.h>
#include <stdlib.h>

#define LAYERS 16

/*----------------- GLOBAL VARIABLES -----------------*/
unsigned char *ptr_stack = NULL,
              *ptr_anchor = NULL,
               stack[LAYERS],
               count_layer = 0;
/*----------------------------------------------------*/

int data_pop();
void show_info();
void show_stack();
void data_add(short int value_to_add);

int main(void) {
    unsigned char choose, confirm;
    short int my_data;
    
    ptr_stack = stack;
    ptr_anchor = stack;
    system("cls");
    show_info();

    do{
        printf("\t\t >> ");
        choose = getchar();
        fflush(stdin);

        switch (choose){
            case '0':
                break;
            case '1':
                puts("\tLembre-se de adicionar um valor que seja menor ou igual a 1 byte.");
                printf("\t\t\tAdicione um valor >> ");
                
                scanf("%hd", &my_data);
                fflush(stdin);

                my_data <= 255 ? data_add(my_data) : puts("Valor maior do que 1 byte, tente novamente");
                break;

            case '2':
                printf("\tTem certeza <s> para confirmar <n> para desisitr >> ");
                confirm = getchar();
                fflush(stdin);

                if (confirm == 'n') break;
                else {
                    data_pop();
                    break;
                }
                puts("Escolha invalida!");
                puts("\t\t\t-----------------\n");
                break;

            case '3':
                break;

            default:
                puts("<ERRO> Item selecionado inexistente, tente novamente.\n");
                break;
        }
    } while (choose != '3');

    puts("Saindo...");
    return 0; /*End of program*/
}

void show_info(){
    puts("\t\t\t1 - Adicionar itens a lista");
    puts("\t\t\t2 - Remover itens da lista");
    puts("\t\t\t3 - Sair do programa");
    puts("\t\t\t---------------------------");
}

void show_stack(){
    printf("\t\t\t\t|         |\n");
    for (int i = count_layer; i != 0; --i){
        printf("\t\t\t\t%X --  %4hd     -- %p   \n", i, stack[i], &stack[i]);
    }
    printf("\t\t\t\t|---------|\n");
    puts("\t\t\t---------------------------");
    show_info();
}

void data_add(short int value_to_add){
    system("cls");

    if (ptr_stack == (ptr_anchor + LAYERS)){
        puts("\t\t\t\t MEMORIA CHEIA!");
        show_stack();
        exit(0); // Finalizando o programa.
    } else {
        puts("\t\t\t Dado inserido com sucesso!");
        ++ ptr_stack;
        *ptr_stack = (unsigned char) value_to_add;
        ++ count_layer;

        show_stack();
    }
}

int data_pop(){
    system("cls");
    if (ptr_stack > ptr_anchor){
        --ptr_stack;
        --count_layer;
        show_stack();
        puts("\t\t\t Indice atual removido com sucesso!");
        return '0';
    } else {
        puts("\t\t\t\t MEMORIA VAZIA");
        show_stack();
        return '0';
    }
}