#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // For uintptr_t
#include <time.h>   // For clock_t, clock(), CLOCKS_PER_SEC

void saxpy_c(int n, float A, float *X, float *Y, float *Z);
extern void asmsaxpy(int n, const float A, const float *X, const float *Y, const float *Z);

// Function to generate a random vector
void generate_random_vector(float *vec, int n)
{
    for (int i = 0; i < n; i++)
    {
        vec[i] = (float)rand() / RAND_MAX; // Random float in [0, 1)
    }
}

int main()
{
    int exp, n, i;
    float A;
    printf("Enter the exponent for vector size (2^exp): ");
    scanf("%d", &exp);
    n = 1 << exp; // Calculate n as 2^exp

    printf("Generated vector size: %d\n", n);
    printf("Enter A: ");
    scanf("%f", &A);

    // Allocate memory for vectors
    float *X = (float *)malloc(n * sizeof(float));
    float *Y = (float *)malloc(n * sizeof(float));
    float *Z_c = (float *)malloc(n * sizeof(float));
    float *Z_asm = (float *)malloc(n * sizeof(float));

    if (!X || !Y || !Z_c || !Z_asm)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Initialize Z_asm to 1.0 to check if array is being passed correctly
    for (int i = 0; i < n; i++)
    {
        Z_asm[i] = 1.0f;
    }

    // Generate random numbers for X and Y
    srand((unsigned)time(NULL)); // Seed the random number generator
    generate_random_vector(X, n);
    generate_random_vector(Y, n);

    // Print generated numbers for debugging or verification
    printf("\nGenerated X vector (first 10 elements):\n");
    for (i = 0; i < (n < 10 ? n : 10); i++)
    {
        printf("X[%d] = %.6f\n", i, X[i]);
    }
    printf("\nGenerated Y vector (first 10 elements):\n");
    for (i = 0; i < (n < 10 ? n : 10); i++)
    {
        printf("Y[%d] = %.6f\n", i, Y[i]);
    }

    struct timespec start, end;

    // Time the C implementation
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (i = 0; i < 100000; i++)
    { // Increased iterations
        saxpy_c(n, A, X, Y, Z_c);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double c_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // Time the Assembly implementation
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (i = 0; i < 100000; i++)
    { // Increased iterations
        asmsaxpy(n, A, X, Y, Z_asm);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double asm_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("\nResults:\n");
    printf("C ver.: ");
    for (i = 0; i < (n < 10 ? n : 10); i++)
    {
        printf("%.2f ", Z_c[i]);
    }
    printf("\nAssembly ver.: ");
    for (i = 0; i < (n < 10 ? n : 10); i++)
    {
        printf("%.2f ", Z_asm[i]);
    }
    printf("\n");

    printf("\nAverage execution time:\n");
    printf("C ver.: %.21f seconds\n", c_time);          // Average per iteration
    printf("Assembly ver.: %.21f seconds\n", asm_time); // Average per iteration

    free(X);
    free(Y);
    free(Z_c);
    free(Z_asm);
    return 0;
}

void saxpy_c(int n, float A, float *X, float *Y, float *Z)
{
    for (int i = 0; i < n; i++)
    {
        Z[i] = A * X[i] + Y[i];
    }
}
