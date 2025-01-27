#include <stdio.h>

void calc(float *v, int num, float *xmin, float *xmax);

int main(void){
    float vetor[] = {10, 20, 30, 40, 50, 11, 12, 5, -33};
    float maior, menor;

    calc(vetor, 9, &menor, &maior);
    printf("Maior elemento %.2f\nMenor elemento %.2f\n", maior, menor);
}

void calc(float *v, int num, float *xmin, float *xmax){
    *xmin = *xmax = *v;

    for (int i = 0; i < num; i++){
        if (v[i] < *xmin) *xmin = v[i];
        if (v[i] > *xmax) *xmax = v[i];
    }
}