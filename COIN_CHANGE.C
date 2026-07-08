#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Swap for sorting
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Sort in descending order
void sortDescending(int coins[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (coins[i] < coins[j])
                swap(&coins[i], &coins[j]);
}

int main() {
    int n, amount;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int coins[n];
    printf("Enter coin denominations:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }

    printf("Enter the amount: ");
    scanf("%d", &amount);

    clock_t start = clock();

    // Sort coins in descending order
    sortDescending(coins, n);

    printf("\nAvailable Denominations (Descending): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", coins[i]);
    }

    printf("\n\nGreedy Coin Selection:\n");

    int count[n];
    for (int i = 0; i < n; i++) count[i] = 0;

    int remaining = amount;

    for (int i = 0; i < n; i++) {
        while (remaining >= coins[i]) {
            remaining -= coins[i];
            count[i]++;
        }
    }

    if (remaining != 0) {
        printf("Cannot make exact change with given denominations.\n");
    } else {
        printf("Coins used:\n");
        int totalCoins = 0;
        for (int i = 0; i < n; i++) {
            if (count[i] > 0) {
                printf("Coin: %d, Count: %d\n", coins[i], count[i]);
                totalCoins += count[i];
            }
        }

        printf("\nOutput Vector (Coin Path): ");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < count[i]; j++) {
                printf("%d ", coins[i]);
            }
        }
        printf("\nTotal Coins Used: %d\n", totalCoins);
    }

    clock_t end = clock();
    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("CPU Time: %.6f seconds\n", cpu_time);

    printf("Time Complexity: O(n log n + amount)\n");
    printf("Space Complexity: O(n)\n");

    return 0;
}
