#include <stdio.h>
#include <math.h>

#define DIM 5

float true_rms(float volts[], int n);

int main(void) {
    float localVetor[DIM] = {0};

    printf("Informe os %d valores do conversor AD \n", DIM);
    for (int i = 0; i < DIM; ++i){
        printf("%d >> ", i + 1);
        scanf("%f", &localVetor[i]);
        fflush(stdin);
    }

    printf("Vrsm= %.4fV\n", true_rms(localVetor, DIM));
}

float true_rms(float volts[], int N){
    float rms = 0.0;

    for (int i = 0; i < N; ++i){
        volts[i] *= volts[i];
        rms += volts[i];
    }

    return sqrt(rms / N);
}