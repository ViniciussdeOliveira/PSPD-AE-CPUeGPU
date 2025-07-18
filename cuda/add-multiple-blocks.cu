#include <iostream>
#include <math.h>

__global__ void add(int n, float *x, float *y) {
  // Calcular índice, o offset é o início do bloco (blockIdx.x * blockDim.x)
  int index = blockIdx.x * blockDim.x + threadIdx.x;

  // Pular pela quantidade de threads por bloco
  int stride = blockDim.x * gridDim.x;
  for (int i = index; i < n; i += stride)
    y[i] = x[i] + y[i];
}

int main(void) {
  int N = 1 << 20;
  float *x, *y;

  cudaMallocManaged(&x, N * sizeof(float));
  cudaMallocManaged(&y, N * sizeof(float));

  for (int i = 0; i < N; i++) {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  int blockSize = 256;
  int numBlocks = (N + blockSize - 1) / blockSize;

  // Fazer prefetch para evitar page faults
  cudaMemPrefetchAsync(x, N * sizeof(float), 0, 0);
  cudaMemPrefetchAsync(y, N * sizeof(float), 0, 0);
  add<<<numBlocks, blockSize>>>(N, x, y);
  cudaDeviceSynchronize();

  float maxError = 0.0f;
  for (int i = 0; i < N; i++) {
    maxError = fmax(maxError, fabs(y[i] - 3.0f));
  }
  std::cout << "Max error: " << maxError << std::endl;

  cudaFree(x);
  cudaFree(y);
  return 0;
}
