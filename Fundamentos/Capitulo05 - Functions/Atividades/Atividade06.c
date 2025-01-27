#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv) {
    float result;

    printf("Resistores: ");
    for (int i = 1; i < argc; i += 2){
        if (atof(argv [i + 1]) != 0.0){
            result = atof(argv[i]) / atof(argv [i + 1]);
            printf("%.1f | ", result);
        } else break;
    }
    printf("ohms.\n");
}
