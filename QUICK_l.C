#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Swap function
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Lomuto Partitioning
int lomutoPartition(int arr[], int low, int high) {
    int pivot = arr[high];  // pivot = last element
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// QuickSort using Lomuto partition
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = lomutoPartition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Main driver
int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    clock_t start = clock(); // Start timer
    quickSort(arr, 0, n - 1);
    clock_t end = clock(); // End timer

    printf("Sorted array using Quick Sort (Lomuto Partition):\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nCPU Time: %.6f seconds\n", cpu_time);

    // Time & Space Complexity
    printf("\nTime Complexity:\n");
    printf("Best Case: O(n log n)\n");
    printf("Average Case: O(n log n)\n");
    printf("Worst Case: O(n^2) [when array is already sorted]\n");

    printf("\nSpace Complexity: O(log n) [due to recursion stack]\n");

    return 0;
}
