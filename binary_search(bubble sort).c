#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

// Bubble sort implementation
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Binary search function that counts comparisons
int binarySearch(int arr[], int n, int target, int *count) {
    int low = 0, high = n - 1;
    *count = 0;
    
    while (low <= high) {
        (*count)++;  // Count each iteration (comparison)
        int mid = low + (high - low) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;  // Target not found
}

int main() {
    int n = 100;         // Array size
    int min = 1;         // Minimum random number
    int max = 5000;      // Maximum random number
    int *arr = malloc(n * sizeof(int));
    if (!arr) {
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }
    
    // Seed the random number generator
    srand(time(0));
    
    // Generate random numbers for the array
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (max - min + 1) + min;
    }
    
    // Optional: Print the unsorted array
    printf("Unsorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Sort the array using bubble sort and measure the sort time
    struct timeval start, end;
    gettimeofday(&start, NULL);
    bubbleSort(arr, n);
    gettimeofday(&end, NULL);
    double sortTime = ((end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec)) / 1000000.0;
    
    // Optional: Print the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // Generate a random target number within the same range
    int target = rand() % (max - min + 1) + min;
    printf("Target: %d\n", target);
    
    // Perform binary search and measure its time and comparisons
    int count = 0;
    gettimeofday(&start, NULL);
    int index = binarySearch(arr, n, target, &count);
    gettimeofday(&end, NULL);
    double searchTime = ((end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec)) / 1000000.0;
    
    if (index != -1)
        printf("Found target %d at index %d\n", target, index);
    else
        printf("Target %d not found in the array\n", target);
    
    printf("Bubble sort time: %f seconds\n", sortTime);
    printf("Binary search time: %f seconds\n", searchTime);
    printf("Binary search comparisons: %d\n", count);
    
    free(arr);
    return 0;
}
