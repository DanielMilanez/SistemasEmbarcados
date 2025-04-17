#include <stdio.h>
#include <stdlib.h>

#define DIM 8
#define clearBuffer() while(getchar() != '\n')

typedef struct {
    unsigned P0: 1,
             P1: 1,
             P2: 1,
             P3: 1,
             P4: 1,
             P5: 1,
             P6: 1,
             P7: 1;
}BIT;

void freeMemory(int **map);
void createMap(int **map);
void showMap(int **map);

void infoManager(int value, int valueY, BIT * data, int ** map);

int main(void) {
    int value, lineSelect;
    BIT data;
    int **map = malloc(DIM * sizeof(int *));

    createMap(map);

    printf("Informe um valor hexadecimal: ");
    scanf("%X", &value);
    clearBuffer();
    
    printf("Informe uma linha para ser alterada: ");
    scanf("%X", &lineSelect);
    clearBuffer();

    infoManager(value, lineSelect, &data, map);
    showMap(map);
    
    printf("\n-------------------------------");
    printf("\n|        VALOR ALTERADO       |");
    printf("\n-------------------------------\n");
    printf("\t%d ", data.P0);
    printf("%d ", data.P1);
    printf("%d ", data.P2);
    printf("%d ", data.P3);
    printf("%d ", data.P4);
    printf("%d ", data.P5);
    printf("%d ", data.P6);
    printf("%d ", data.P7);
    printf("\n-------------------------------\n");

    freeMemory(map);
    return 0;
}

// Memory alocation managers
void createMap(int **map){
    for (int i = 0; i < DIM; ++i) {
        map[i] = calloc(DIM, sizeof(int));
    }
}
void freeMemory(int **map) {
    for (int i = 0; i < DIM; ++i){
        free(map[i]);
    }
    free(map);
}
void showMap(int **map){
    for (int i = 7; i >= 0; --i){
        for (int j = 7; j >= 0; --j){
            printf("%2d", map[i][j]);
        }
        putchar('\n');
    }
}

// Other funcionts
void infoManager(int value, int valueY, BIT * data, int ** map){
    for (int i = 7; i >= 0; --i){
        if (i == valueY){
            for (int j = 7; j >= 0; --j){
                map[i][j] = (value >> j) & 1;
            }
        }
    }
    data->P0 = (value >> 7) & 1;
    data->P1 = (value >> 6) & 1;
    data->P2 = (value >> 5) & 1;
    data->P3 = (value >> 4) & 1;
    data->P4 = (value >> 3) & 1;
    data->P5 = (value >> 2) & 1;
    data->P6 = (value >> 1) & 1;
    data->P7 = (value >> 0) & 1;
}
