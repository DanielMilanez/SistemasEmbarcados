#include <stdio.h>

void show(int var, int *ptr_var);
void update(int *p);

int main(void){
    int var = 15; 
    // Um ponteiro é um apontador para um endereço de memória
    // Uma variável que contem o endereço de memória de outra

    // Para declarar um ponteiro em C utilizamos o operador unário "*"
    // O ponteiro precisa ser do mesmo tipo da variável que ele aponta
    int *ptr_var = NULL; // Sempre começe com null seus ponteiros quando não inicializados
    ptr_var = &var; /* Recebe o endereço de var se var fosse um vetor poderiamos passar apenas o
    nome do próprio vetor em si sem a necessidade de do "&" */

    printf("valor original de var: %p \n", ptr_var);
    printf("valor original de ptr_var: %p \n", &ptr_var);
    show(var, ptr_var); /*Lembrando que por estar sendo armazenado em uma função, e esta por 
    sua vez é so executada quando é criada, e suas variáveis locais vão ser destruidas, as 
    informações podem estar diferentes da realidade, pois suas variáveis locais possuem um
    espaço na memória, estou utilziando isso para evitar a repetição de código, e isso é
    apenas para exemplificar o conteudo*/

    /*As variaveis possuem um endereço fisico na memória do computador
    e com esse endereço armazenamos valores*/

    // *ptr ---> O conteudo do endereço apontado por
    //  ptr ---> endereço da variável salva em ptr
    // &ptr ---> endereço de ptr

    *ptr_var = 78; // Atualizando o conteudo de maneira indireta
    //update(&ptr_var); // Atualizando a variável com um ponteiro de uma função
    printf("\n\nAtualizando valor de var de forma indireta\n");
    show(var, ptr_var);

}

void show(int var, int *ptr_var){
    printf("Condeutdo de var: %d\n", var);
    printf("Address de var na func: %p\n\n", &var);

    printf("Condeutdo de var apontado por ptr: %d\n", *ptr_var);
    printf("Address de var salvo em ptr: %p\n", ptr_var);
    printf("Address de ptr: %p\n", &ptr_var);

}
