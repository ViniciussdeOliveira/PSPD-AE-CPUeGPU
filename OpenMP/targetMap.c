#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

// Função que realiza a soma de dois vetores utilizando GPU com OpenMP
void soma_gpu(float *a, float *b, float *resultado, int n) {

    // Diretiva OpenMP para offload do bloco de código para o dispositivo (ex: GPU)
    // 'map(to: a[0:n], b[0:n])' indica que os vetores 'a' e 'b' devem ser copiados da CPU para a GPU
    // 'map(from: resultado[0:n])' indica que o vetor 'resultado' será copiado da GPU de volta para a CPU após a execução
    #pragma omp target map(to: a[0:n], b[0:n]) map(from: resultado[0:n])

    // Diretiva OpenMP para paralelizar o loop 'for' na GPU
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        // Soma elemento a elemento dos vetores 'a' e 'b', armazenando o resultado no vetor 'resultado'
        resultado[i] = a[i] + b[i];
    }
}

int main() {
    int n = 1000000;
    float *a = (float *)malloc(n * sizeof(float));
    float *b = (float *)malloc(n * sizeof(float));
    float *resultado = (float *)malloc(n * sizeof(float));

    // Inicializa os vetores
    for (int i = 0; i < n; i++) {
        a[i] = i * 1.0f;
        b[i] = i * 2.0f;
    }

    // Soma vetores na GPU
    soma_gpu(a, b, resultado, n);

    // Mostra os 5 primeiros resultados
    for (int i = 0; i < 5; i++) {
        printf("resultado[%d] = %.2f\n", i, resultado[i]);
    }

    free(a);
    free(b);
    free(resultado);
    return 0;
}