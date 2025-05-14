#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void menu();
void help();
void run(int withsound, unsigned rep, char *mensage);

int main(void) {
    char comand[20], text[120] = {'\0'};
    unsigned rep = 0;

    menu();

    do{
        printf(">>> ");
        gets(comand);
        fflush(stdin);

        if (!strcmp(comand, "TEXT")){ 
            printf("Insira o texto >> ");
            gets(text);
            fflush(stdin);
        }

        else if (!strcmp(comand, "HELP")) help();

        else if (!strcmp(comand, "CLEAR")) system("cls");

        else if (!strcmp(comand, "RUN")) run(0, rep, text);

        else if (!strcmp(comand, "CLEAR ALL")) {
            system("cls");
            text[0] = '\0';
            rep = 0;
        }  

        else if (!strcmp(comand, "RUN SOUND")) run(1, rep, text);
        
        else if (!strcmp(comand, "MENU")) menu();

        else if (!strcmp(comand, "REP")) {
            printf("Insira o valor de rep: ");
            scanf("%d", &rep);
            fflush(stdin);
        }

        else printf("Comando invalido tente novamente. \n");

    } while(strcmp(comand, "EXIT"));
    
}

void menu(){
    system("cls");
    printf("------------------\n");
    printf("|                |\n");
    printf("| Interpretador! |\n");
    printf("|                |\n");
    printf("------------------\n");

    printf("\n Insira seu comando para que o interpretador execute-o\n\n");

    printf("- RUN \n- RUN SOUND \n- REP \n- TEXT \n- CLEAR\n- CLEAR ALL\n- EXIT\n- HELP\n\n");
}

void help(){
    system("cls");
    puts("Versao 0.0.1");
    puts("- RUN: rodar o interpretador");
    puts("- RUN SOUND: rodar o interpretador com \"bips\"");
    puts("- REP: define o numero de rep. de uma frase salva previamente com o comando TXT. Recebe o numero de rep. desejadas");
    puts("- TEXT: comando para a entrada de uma nova frase. O arguemnto e a frase-texto que o usuario quiser que o interp rode");
    puts("- CLEAR: limpa a tela do console");
    puts("- CLEAR ALL: limpa a tela e restaura as variaveis");
    puts("- EXIT: encerra o programa");
    puts("- HELP: apresenta a versao atual do interpretador e uma breve explicacao sobre os comandos");
    puts("- MENU: Exibe o menu inical");
}

void run(int withsound, unsigned rep, char *mensage){
    if (rep != 0 && mensage[0] != '\0'){     
        system("cls");
        for (unsigned i = 0; i < rep; ++i){
            for (unsigned j = 0; j < strlen(mensage); ++j){
                withsound != 0 ? printf("\a%c", mensage[j]) : printf("%c", mensage[j]);
            }
            printf("\n");
        }        
    } else puts("Nenhum valor repeat ou text informado, por favor insira-os");
}
