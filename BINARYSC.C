#include <stdio.h>

int binarySearch(int arr[], int item, int low, int high) {
    if (high <= low)
        return (item > arr[low]) ? (low + 1) : low;

    int mid = (low + high) / 2;

    if (item == arr[mid])
        return mid + 1;

    if (item > arr[mid])
        return binarySearch(arr, item, mid + 1, high);
    return binarySearch(arr, item, low, mid - 1);
}

void binaryInsertionSort(int arr[], int n) {
    int i, loc, j, selected;

    for (i = 1; i < n; i++) {
        j = i - 1;
        selected = arr[i];

        loc = binarySearch(arr, selected, 0, j);

        while (j >= loc) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = selected;
    }
}

int main() {
    int arr[100], n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    binaryInsertionSort(arr, n);

    printf("Sorted Array:\n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    return 0;
}
