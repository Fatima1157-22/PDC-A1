#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//We are going to find the nTotal numbers greater than a threshold in an arrray.

#define N 100000000
#define THRESHOLD 500000


//Function to find number
int maxNumbers(int *array, int size, int threshold){
    //Variable to store the count
    int count =0;

    //Now we will loop through each number in an array
    for( int i = 0; i < size; i++){
        //checking if number present in an array is greater than our given threshold
        if(array[i] > threshold){
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
    clock_t start_time = clock();

    int count = maxNumbers(array, N, THRESHOLD);

    //stop measuring execution time
    clock_t end_time = clock();


    double execution_time = (double)(end_time - start_time)/ CLOCKS_PER_SEC;

    //printing the results
    printf("Total numbers greater than threshold %d: %d\n", THRESHOLD, count);
    printf("Execution Time for sequential code: %f seconds\n", execution_time);

    free(array);
    
    return 0;
}