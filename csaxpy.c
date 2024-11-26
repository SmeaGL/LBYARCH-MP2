#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // For uintptr_t
#include <time.h>   // For clock_t, clock(), CLOCKS_PER_SEC

void saxpy_c(int n, float A, float* X, float* Y, float* Z);
extern void asmsaxpy(int n, float A, float* X, float* Y, float* Z);

void input_vectors(int n, float* X, float* Y) {
    for (int i = 0; i < n; i++) {
        printf("X[%d]: ", i);
        scanf("%f", &X[i]);
    }
    for (int i = 0; i < n; i++) {
        printf("Y[%d]: ", i);
        scanf("%f", &Y[i]);
    }
}

int main() {
    int n, i;
    float A;
    printf("Size n: ");
    scanf("%d", &n);
    printf("Enter A: ");
    scanf("%f", &A);

    // Regular malloc
    float* X = (float*)malloc(n * sizeof(float));
    float* Y = (float*)malloc(n * sizeof(float));
    float* Z_c = (float*)malloc(n * sizeof(float));
    float* Z_asm = (float*)malloc(n * sizeof(float));

    if (!X || !Y || !Z_c || !Z_asm) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    input_vectors(n, X, Y);

    struct timespec start, end;

    // Time the C implementation
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (i = 0; i < 100000; i++) { // Increased iterations
        saxpy_c(n, A, X, Y, Z_c);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double c_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // Time the Assembly implementation
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (i = 0; i < 100000; i++) { // Increased iterations
        asmsaxpy(n, A, X, Y, Z_asm);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double asm_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("\nResults:\n");
    printf("C ver.: ");
    for (i = 0; i < (n < 10 ? n : 10); i++) {
        printf("%.2f ", Z_c[i]);
    }
    printf("\nAssembly ver.: ");
    for (i = 0; i < (n < 10 ? n : 10); i++) {
        printf("%.2f ", Z_asm[i]);
    }
    printf("\n");

    printf("\nAverage execution time:\n");
    printf("C ver.: %.21f seconds\n", c_time); // Average per iteration
    printf("Assembly ver.: %.21f seconds\n", asm_time); // Average per iteration

    free(X);
    free(Y);
    free(Z_c);
    free(Z_asm);
    return 0;
}

void saxpy_c(int n, float A, float* X, float* Y, float* Z) {
    for (int i = 0; i < n; i++) {
        Z[i] = A * X[i] + Y[i];
    }
}
