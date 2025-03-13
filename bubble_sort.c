#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

// Bubble sort implementation that counts swap operations
long bubbleSort(int arr[], int n) {
    long swapCount = 0;
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        // Flag to detect if any swap happened in this pass.
        int swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap the elements
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapCount++;
                swapped = 1;
            }
        }
        // If no swap happened, the array is already sorted.
        if (!swapped)
            break;
    }
    return swapCount;
}

int main() {
    // Array sizes to test
    int sizes[] = {10, 50,100,1000,2000,3000,4000, 5000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    
    // Seed random number generator
    srand(time(0));
    
    // Print CSV table header
    printf("Array_Size,Time_Taken_Seconds,Swap_Count\n");
    
    for (int k = 0; k < numSizes; k++) {
        int n = sizes[k];
        int *arr = malloc(n * sizeof(int));
        if (!arr) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        
        // Generate random numbers for the array (range: 1 to 5000)
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 5000 + 1;
        }
        
        struct timeval start, end;
        gettimeofday(&start, NULL);
        
        // Perform bubble sort and count swaps
        long swapCount = bubbleSort(arr, n);
        
        gettimeofday(&end, NULL);
        
        // Calculate time taken in seconds (with microsecond precision)
        double timeTaken = ((end.tv_sec - start.tv_sec) * 1000000.0 + 
                             (end.tv_usec - start.tv_usec)) / 1000000.0;
                             
        // Print the results in CSV format
        printf("%d,%f,%ld\n", n, timeTaken, swapCount);
        
        free(arr);
    }
    
    return 0;
}
