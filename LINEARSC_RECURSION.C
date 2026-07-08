#include <stdio.h>

int linearSearchRecursive(int arr[], int n, int key, int index) {
    if (index >= n)
        return -1;
    if (arr[index] == key)
        return index;
    return linearSearchRecursive(arr, n, key, index + 1);
}

int main() {
    int arr[100], n, key;
    printf("Enter array size: ");
    scanf("%d", &n);

    printf("Enter array elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter element to search: ");
    scanf("%d", &key);

    int result = linearSearchRecursive(arr, n, key, 0);
    if (result != -1)
        printf("Element found at index: %d\n", result);
    else
        printf("Element not found.\n");

    return 0;
}
