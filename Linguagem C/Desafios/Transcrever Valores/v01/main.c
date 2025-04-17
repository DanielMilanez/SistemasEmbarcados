#include <stdio.h>
#include <stdlib.h>

typedef struct{
    unsigned P0: 1,
             P1: 1,
             P2: 1,
             P3: 1,
             P4: 1,
             P5: 1,
             P6: 1,
             P7: 1;
}BIT;

int AskForUse(void);
void DataManager(int value, int * map, BIT * info);

int main(void){
    BIT info;
    int value = 0;

    int * map = (int *) calloc(8, sizeof(int));

    value = AskForUse();
    DataManager(value, map, &info);

    for (int i = 7; i >= 0; --i){
        printf("%d ", map[i]);
    }

    putchar('\n');
    printf("%d ", info.P0);
    printf("%d ", info.P1);
    printf("%d ", info.P2);
    printf("%d ", info.P3);
    printf("%d ", info.P4);
    printf("%d ", info.P5);
    printf("%d ", info.P6);
    printf("%d ", info.P7);

    free(map);
    return 0;
}

int AskForUse(void){
    int data = 0;

    printf("Informe um valor hexadecimal: ");
    scanf("%X", &data);
    fflush(stdin);

    return data;
}

void DataManager(int value, int * map, BIT * info){
    printf("Processo de escrita \n");
    for (int i = 7; i >= 0; --i){
        map[i] = (value >> i) & 1;
        printf("%d - %d \n", i , map[i]);
    }
    printf("--------------------\n");

    info->P0 = map[0];
    info->P1 = map[1];
    info->P2 = map[2];
    info->P3 = map[3];
    info->P4 = map[4];
    info->P5 = map[5];
    info->P6 = map[6];
    info->P7 = map[7];
}
