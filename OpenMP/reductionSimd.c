#include <stdio.h>
#include <omp.h>

#define TAM 1000

int main() {
    float vetor[TAM];
    float soma = 0.0f;

    // Inicializa o vetor com valores simples
    for (int i = 0; i < TAM; i++) {
        vetor[i] = 1.0f; // Cada elemento vale 1.0
    }

    // Paraleliza a soma com OpenMP SIMD e cláusula reduction
    #pragma omp simd reduction(+:soma)
    for (int i = 0; i < TAM; i++) {
        soma += vetor[i];
    }

    printf("Soma dos elementos: %.2f\n", soma); // Esperado: 1000.00

    return 0;
}