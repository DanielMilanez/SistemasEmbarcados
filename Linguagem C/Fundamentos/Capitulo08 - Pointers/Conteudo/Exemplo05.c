#include <stdio.h>
#include <string.h>

int main(void){
    char str[31] = "Linuagem C";
    char str2[31];
    char *ptr_str = str; 

    strcpy(str2, str);

    printf("Info. salva >> %s\n", str);

    putchar('\n');
    printf("%s << Acessando o valor completo usando a string\n", str);
    printf("%c << Usando um ponteiro para acessar o primeiro indice\n", *ptr_str);

    putchar('\n');
    printf("%X << Vendo addrress salvo do primeiro indice da string\n", &str); 
    printf("%X << Vendo addrress salvo usando o ponteiro\n\n", ptr_str); 

    *(ptr_str + 9) = 'D';
    printf("Atualizando a mensagem com um ponteiro acessando o indice 10 >> %s\n\n", str);

    // Podemos varrer a string completa com um ponteiro e ir atualizando os caracteres
    for (unsigned i = 0; i < strlen(str); ++i){
        *(ptr_str + i) = '-';
    }
    puts("Atualizando os caracteres da string com um loop for\n");
    puts(str2);
    puts(str);
    putchar('\n');
    strcpy(str2, str);

    // Podemos varrer a string completa com um ponteiro e ir atualizando os caracteres
    for (unsigned i = 0; i < strlen(str); ++i){
        *(ptr_str + i) = 0x30 + i; // 0 da tabela ASCII + I
    }
    puts("Atualizando novamente da string com um loop for\n");
    puts(str2);
    puts(str);
}