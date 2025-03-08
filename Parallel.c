#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 100000000  // Large array size

int count_odd_numbers_parallel(int *array, int size) {
    int count = 0;

    // Uncomment only ONE of these at a time to test:
    // Method 1: Critical Section (Slowest)
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < size; i++) {
        if (array[i] % 2 != 0) {
            #pragma omp critical
            count++;
        }
    }

    // Method 2: Atomic Operation (Faster)
    // #pragma omp parallel for schedule(static)
    // for (int i = 0; i < size; i++) {
    //     if (array[i] % 2 != 0) {
    //         #pragma omp atomic
    //         count++;
    //     }
    // }

    // Method 3: Reduction (Fastest)
    // #pragma omp parallel for reduction(+:count) schedule(static)
    // for (int i = 0; i < size; i++) {
    //     if (array[i] % 2 != 0) {
    //         count++;
    //     }
    // }

    return count;
}

int main() {
    int *array = (int *)malloc(N * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        array[i] = rand();  // Generate random numbers
    }

    double start_time = omp_get_wtime();
    int odd_count = count_odd_numbers_parallel(array, N);
    double end_time = omp_get_wtime();

    printf("Total Odd Numbers: %d\n", odd_count);
    printf("Parallel Execution Time: %f seconds\n", end_time - start_time);

    free(array);
    return 0;
}
