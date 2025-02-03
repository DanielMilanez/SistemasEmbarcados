#include <stdio.h>
#include <stdlib.h>

void countNumbers(int number);

int main(void) {
    int number;

    scanf("%d", &number);
    fflush(stdin);
    countNumbers(number);
}

void countNumbers(int number){
    static int i = 0;
    if (i == number) return;
    else {
        ++i;
        printf("%d ", i);
        countNumbers(number);
    }
}