#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *arq_bin;

    if ((arq_bin = fopen("arq.bin", "rb")) == NULL) exit(2);
        
        fseek(arq_bin, 0, SEEK_END);
        printf("%ld bytes", ftell(arq_bin));

    fclose(arq_bin);
}
