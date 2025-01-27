#include <stdio.h>
#include <stdlib.h>

void dispmat(char **m, int n);

int main(void) {
    char *matrix[] = {"Aurora", 
                      "Linguagem C",
                      "Aprendendo C!"};

    dispmat(matrix, 3);
}

void dispmat(char **m, int n){
    for (int i = 0; i < n; ++i){
        printf("%s\n", m[i]);
    }
}