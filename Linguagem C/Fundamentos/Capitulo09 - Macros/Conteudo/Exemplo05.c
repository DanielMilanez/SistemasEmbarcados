/*Eliminando a necessidade de utilização de aspas*/
#include <stdio.h>
#include <stdlib.h>

#define disp(text) printf(#text)
#define numbers(index) id##index

int main(void){
    int id1 = 50,
        id2 = 10,
        id3 = 14,
        id4 = 18;

    disp(Aqui sem aspas!!!\n);

    printf("%d\n", numbers(1));
    printf("%d\n", numbers(2));
    printf("%d\n", numbers(3));
    printf("%d\n", numbers(4));
}