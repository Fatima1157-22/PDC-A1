#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

//We are going to find the nTotal numbers greater than a threshold in an arrray.

#define N 100000000
#define THRESHOLD 500000


//Function to find number using OpenMp
int maxNumbers(int *array, int size){
    //Variable to store the count
    int count =0;

    //First try to get parallelization using Critical
    #pragma omp parallel for schedule(static)
    for( int i = 0; i < size; i++){
        if(array[i] > THRESHOLD){
            #pragma omp critical
            count++;
        }
    }
    return count;
}

int main(){
    /* We are dynamically allocation our array as stack memory can lead to stack 
        overflow. malloc() method helps us allocate the memory in heap which helps
        in handling large memory allocations. 
    */
    int *array = (int *)malloc(N * sizeof(int));
    if( array == NULL){
        printf("Memory Allocation Failed!\n");
        return 1;
    }

    //Initializing random number generator
    srand(time(NULL));

    //Filling array with random Numbers
    for( int i = 0; i < N; i++){
        array[i] = rand() % 1000000;
    }

    //Start measuring execution time
    double start_time = omp_get_wtime();

    int count = maxNumbers(array, N);

    //stop measuring execution time
    double end_time = omp_get_wtime();


    //printing the results
    printf("Total numbers greater than threshold %d: %d\n", THRESHOLD, count);
    printf("Execution Time for sequential code: %f seconds\n",end_time - start_time);

    free(array);
    
    return 0;
}