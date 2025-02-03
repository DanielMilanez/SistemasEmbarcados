/*Ponteiros para estruturas*/
#include <stdio.h>
#include <stdlib.h>

struct drinks {
    int margarita,
        dry_martini,
        caipirinha;
}open_bar;

struct drinks *cheers; /* Ponteiro para uma variável complexa */

void barman(struct drinks *p);

int main(void){
    barman(&open_bar);

    // cheers = &open_bar;
    // cheers -> margarita = 741;

    printf("%4d\n",open_bar.margarita); 
    printf("%4d\n",open_bar.dry_martini); 
    printf("%4d\n",open_bar.caipirinha); 

    // cheers = &open_bar;

    /*Para acessar um membro de uma estrutura a patrir de um ponteiro utilzie o operador "->" */
    // cheers->margarita = 31;
    // (*cheers).margarita = 31;

    // barman(open_bar);

    // printf("%p\n", open_bar);
    // printf("%d\n", open_bar->margarita);
    // printf("%d\n", open_bar->dry_martini);
    // printf("%d\n", open_bar->caipirinha);
    return 0;
}

void barman(struct drinks *p){
    p->margarita = 19;
    p->dry_martini = 21;
    p->caipirinha = 43;
}
