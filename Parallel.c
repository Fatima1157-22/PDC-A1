#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

//We are going to find the nTotal numbers greater than a threshold in an arrray.

#define N 100000000
#define THRESHOLD 500000


//Function to find number using OpenMp
int maxNumbers(int *array, int size, int chunk_size){
    //Variable to store the count
    int count =0;

    omp_set_num_threads(16);

    /*First try to get parallelization using Critical
    Critical made the execution time go near 15 sec which is not even beteer than seq. 0.8 sec.*/
    
    // #pragma omp parallel for schedule(dynamic, chunk_size)
    // for( int i = 0; i < size; i++){
    //     if(array[i] > THRESHOLD){
    //         #pragma omp critical
    //         count++;
    //     }
    // }

    //Doing atomic but execution time does not make any fine difference but better than critical not seq.
    // #pragma omp parallel for schedule(dynamic, chunk_size)
    // for( int i = 0; i < size; i++){
    //     if(array[i] > THRESHOLD){
    //         #pragma omp atomic
    //         count++;
    //     }
    // }

    //Using reduction method and achieved the result at its best 0.091 sec.
    #pragma omp parallel for reduction(+:count) schedule(dynamic, chunk_size)
    for( int i = 0; i < size; i++){
        if(array[i] > THRESHOLD){
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
    //defining different chunk sizes
    int chunk_sizes[]= {1000,10000,100000,500000};
    int num_chunks = sizeof(chunk_sizes)/sizeof(chunk_sizes[0]);

    printf("Chunk sizes\tExecution Time (seconds)\n");
    printf("-------------------------------------\n");


    for(int i =0; i <num_chunks; i++){

        //Start measuring execution time
        double start_time = omp_get_wtime();
        int count = maxNumbers(array, N, chunk_sizes[i]);
        
        //stop measuring execution time
        double end_time = omp_get_wtime();

        //printing the results
        printf("%d\t\t%f\n", chunk_sizes[i], end_time - start_time);
    }
    
    
    // printf("Total numbers greater than threshold %d: %d\n", THRESHOLD, count);
    // printf("Execution Time for parallel code: %f seconds\n",end_time - start_time);

    free(array);
    
    return 0;
}