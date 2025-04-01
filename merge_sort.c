#include <stdio.h>

#define MAX 10

int a[11] = { 10, 14, 19, 26, 27, 31, 33, 35, 42, 44, 0 }; // Size 11 because there's an extra element (0)
int b[10]; // Temporary array for merging

void merging(int low, int mid, int high) {
    int l1 = low, l2 = mid + 1, i;

    for (i = low; l1 <= mid && l2 <= high; i++) {
        if (a[l1] <= a[l2]) {
            b[i] = a[l1++];
        } else {
            b[i] = a[l2++];
        }
    }

    while (l1 <= mid) { // Copy remaining elements of left subarray
        b[i++] = a[l1++];
    }

    while (l2 <= high) { // Copy remaining elements of right subarray
        b[i++] = a[l2++];
    }

    for (i = low; i <= high; i++) {
        a[i] = b[i]; // Copy the sorted elements back to the original array
    }
}

void sort(int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        sort(low, mid);
        sort(mid + 1, high);
        merging(low, mid, high);
    }
}

int main() {
    int i;

    printf("List before sorting:\n");

    for (i = 0; i <= MAX; i++) {
        printf("%d ", a[i]);
    }

    sort(0, MAX);

    printf("\nList after sorting:\n");

    for (i = 0; i <= MAX; i++) {
        printf("%d ", a[i]);
    }

    return 0;
}
