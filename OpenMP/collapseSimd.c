#include <stdio.h>
#include <omp.h>

#define N 4
#define M 4

int main() {
    float A[N][M], B[N][M], C[N][M];

    // Inicializa as matrizes A e B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }

    // Multiplicação elemento a elemento usando OpenMP SIMD com collapse
    #pragma omp simd collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            C[i][j] = A[i][j] * B[i][j];
        }
    }

    // Impressão do resultado
    printf("Matriz C (resultado da multiplicação elemento a elemento):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%6.2f ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}