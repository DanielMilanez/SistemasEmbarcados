#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dependences.c"

int main(void) {

    int found = 0;
    char user[STR_SIZE],
         password[STR_SIZE];

    do{
        printf("Informe o usuario >> ");
        gets(user);
        fflush(stdin);

        printf("Informe a senha >> ");
        gets(password);
        fflush(stdin);

        for (int i = 0; i < DIM; i++) {
            if ((strcmp(clerklist[i].user, user) == 0) && (strcmp(clerklist[i].password, password) == 0)) {
                found = 1;
                break;
            }
        }
        show_menu(found);

    } while(!found);

    return 0;
}