#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

// Função que multiplica cada elemento de um vetor por um escalar
void multiplicar_escalar(float *vetor, float escalar, int n) {
    // Diretiva OpenMP que combina paralelismo de múltiplas threads (parallel for)
    // com vetorização SIMD (simd) para otimizar a execução da iteração do laço
    #pragma omp parallel for simd
    for (int i = 0; i < n; i++) {
        // Multiplica o elemento i do vetor pelo escalar fornecido
        vetor[i] *= escalar;
    }
}

int main() {
    int n = 1000;
    float escalar = 2.5;
    float *vetor = (float *)malloc(n * sizeof(float));

    // Inicializa o vetor
    for (int i = 0; i < n; i++) {
        vetor[i] = i * 1.0f;
    }

    // Multiplica com OpenMP + SIMD
    multiplicar_escalar(vetor, escalar, n);

    // Mostra os 5 primeiros resultados
    for (int i = 0; i < n; i++) {
        printf("vetor[%d] = %.2f\n", i, vetor[i]);
    }

    free(vetor);
    return 0;
}