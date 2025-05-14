#include <stdio.h>
#include <stdlib.h>

# define DIM 200

void criptografy(char *mensage, FILE *file);

int main(void) {
    FILE *my_file;

    char mensage[DIM],
         file_name[DIM];
        
    printf("Digite o nome do arquivo: ");
    scanf("%s", file_name);
    fflush(stdin);

    if ((my_file = fopen(file_name, "w+")) == NULL){
        puts("ERRO FATAL.");
        system("PAUSE");
        exit(0);
    }

    printf("Informe a mensagem para a criptografia >> ");
    gets(mensage);
    
    criptografy(mensage, my_file);

    fclose(my_file);
}

void criptografy(char *mensage, FILE *new_file){
    for (int i = 0; mensage[i] != '\0'; ++i){
        int temp = (int)mensage[i];
        temp += 3;
        mensage[i] = (char)temp;
        fputc(mensage[i], new_file);
    }
}
