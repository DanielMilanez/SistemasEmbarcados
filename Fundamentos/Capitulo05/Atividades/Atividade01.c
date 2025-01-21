#include <stdio.h>
#include <stdbool.h>

void asteristicos();

int main(void) {
    unsigned num;

    while (true) {
        printf("Digite um numero: ");
        scanf("%d", &num);
        fflush(stdin);

        if (num == 7) asteristicos();
        if (!num) break; // processamento mais rápido!
    }
}

void asteristicos() {
    for (char ast = 0; ast < 10; ++ast){
        putchar('*');
    }
    putchar('\n');
}