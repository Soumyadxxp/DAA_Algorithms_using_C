#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Swap helper
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Hoare Partition
int hoarePartition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low - 1;
    int j = high + 1;

    while (1) {
        // Move right until we find element >= pivot
        do {
            i++;
        } while (arr[i] < pivot);

        // Move left until we find element <= pivot
        do {
            j--;
        } while (arr[j] > pivot);

        // If pointers cross, return
        if (i >= j)
            return j;

        // Swap elements at i and j
        swap(&arr[i], &arr[j]);
    }
}

// Quick Sort using Hoare Partition
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = hoarePartition(arr, low, high);
        quickSort(arr, low, p);
        quickSort(arr, p + 1, high);
    }
}

// Driver/Main function
int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    clock_t start = clock(); // start CPU time
    quickSort(arr, 0, n - 1);
    clock_t end = clock(); // end CPU time

    printf("Sorted array using Quick Sort (Hoare Partition):\n");
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
