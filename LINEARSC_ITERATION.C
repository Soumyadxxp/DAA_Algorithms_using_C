#include <stdio.h>

int linearSearchIterative(int arr[], int n, int key) {
    for (int i = 0; i < n; i++)
        if (arr[i] == key)
            return i;
    return -1;
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

    int result = linearSearchIterative(arr, n, key);
    if (result != -1)
        printf("Element found at index: %d\n", result);
    else
        printf("Element not found.\n");

    return 0;
}
