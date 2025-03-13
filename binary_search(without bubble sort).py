#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Binary search function that also counts comparisons
int binarySearch(int arr[], int n, int target, int *count) {
    int low = 0, high = n - 1;
    *count = 0;
    
    while(low <= high) {
        (*count)++;  // Increment comparison count for each iteration
        int mid = low + (high - low) / 2;
        if(arr[mid] == target) {
            return mid;
        } else if(arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;  // Target not found
}

int main() {
    int n = 100;         // Size of the array
    int min = 1;         // Minimum value for random numbers
    int max = 5000;      // Maximum value for random numbers
    int arr[n];
    int i;
    
    // Seed the random number generator
    srand(time(0));

    // Generate random numbers and fill the array
    for(i = 0; i < n; i++) {
        arr[i] = rand() % (max - min + 1) + min;
    }
    
    // Sort the array for binary search
    qsort(arr, n, sizeof(int), compare);
    
    // Print the sorted array (optional)
    printf("Sorted array: ");
    for(i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Generate a random target within the range
    int target = rand() % (max - min + 1) + min;
    printf("Target: %d\n", target);

    // Perform binary search and count comparisons
    int count = 0;
    int index = binarySearch(arr, n, target, &count);
    
    if(index != -1)
        printf("Found target %d at index %d\n", target, index);
    else
        printf("Target %d not found in the array\n", target);
    
    printf("Number of comparisons: %d\n", count);
    
    return 0;
}
