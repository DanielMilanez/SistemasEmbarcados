/*É possível utilizar qualquer tipo de comando em uma macro.*/
#include <stdio.h>
#include <stdlib.h>

#define maior(a, b) a > b ? a : b

int main(void){
    int result;
    result = maior(9, 5);

    printf("%d\n", result);

}