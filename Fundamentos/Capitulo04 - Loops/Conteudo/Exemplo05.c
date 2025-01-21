// Escrevendo a tabela ASCII
#include <stdio.h>

int main(void){
    int i;
    
    for (i = 0; i < 255; i++){
        printf("%3d -> %c\n", i, (char)i);
    }
}
