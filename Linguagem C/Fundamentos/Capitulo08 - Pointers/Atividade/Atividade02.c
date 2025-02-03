#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char protocol(int op1, int op2);
void result(int op1, int op2, char (func) (int, int));

int main(void) {
    int operando1, 
        operando2;
    
    printf("Informe os valores do primeiro e segundo operandos >> ");
    scanf("%d %d", &operando1, &operando2);

    result(operando1, operando2, protocol);
}

char protocol(int op1, int op2){
    char response;
    response = op1 > op2 ? 'H' : 'L';
    return response;
}

void result(int op1, int op2, char (func)(int, int)){
    printf("Resultado do protocolo: %c", (func) (op1, op2));
}