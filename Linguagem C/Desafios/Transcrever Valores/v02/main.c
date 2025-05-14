#include <stdio.h>
#include <stdlib.h>
typedef struct{
    unsigned P0 : 1,
        P1 : 1,
        P2 : 1,
        P3 : 1,
        P4 : 1,
        P5 : 1,
        P6 : 1,
        P7 : 1;
} BIT;

#define DIM 8
#define clearBuffer() while (getchar() != '\n')

void freeMemory(int **map);
void createMap(int **map);
void showMap(int **map);

void drawLineSelect(BIT *data);
void informationCarrier(BIT *data, int information);
void infoManager(int value, int valueY, BIT *data, int **map);

int main(void){
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
    for (int i = 0; i < DIM; ++i){
        map[i] = calloc(DIM, sizeof(int));
    }
}
void freeMemory(int **map){
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
void infoManager(int value, int valueY, BIT *data, int **map){
    int lineConversor = 0;

    for (int i = 7; i >= 0; --i){
        if (i == valueY){
            for (int j = 7; j >= 0; --j){
                map[i][j] = (value >> j) & 1;
            }
        }
    }

    switch (valueY){
    case 1:
        lineConversor = 0x01;
        break;
    case 2:
        lineConversor = 0x02;
        break;
    case 3:
        lineConversor = 0x04;
        break;
    case 4:
        lineConversor = 0x08;
        break;
    case 5:
        lineConversor = 0x10;
        break;
    case 6:
        lineConversor = 0x20;
        break;
    case 7:
        lineConversor = 0x40;
        break;
    case 8:
        lineConversor = 0x080;
        break;
    default:
        valueY = 1;
        lineConversor = 0x01;
        break;
    }
    informationCarrier(data, lineConversor);
    drawLineSelect(data);
    informationCarrier(data, value);
}
void informationCarrier(BIT *data, int information){
    data->P0 = (information >> 7) & 1;
    data->P1 = (information >> 6) & 1;
    data->P2 = (information >> 5) & 1;
    data->P3 = (information >> 4) & 1;
    data->P4 = (information >> 3) & 1;
    data->P5 = (information >> 2) & 1;
    data->P6 = (information >> 1) & 1;
    data->P7 = (information >> 0) & 1;
}

void drawLineSelect(BIT *data){
    printf("Linha selecionada >> ");
    printf("\t%d ", data->P0);
    printf("%d ", data->P1);
    printf("%d ", data->P2);
    printf("%d ", data->P3);
    printf("%d ", data->P4);
    printf("%d ", data->P5);
    printf("%d ", data->P6);
    printf("%d \n", data->P7);
}
