#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int weight;
    int profit;
    float ratio;
} Item;

// Swap function for sorting
void swap(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

// Sort items by profit/weight ratio in descending order
void sortItems(Item items[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (items[i].ratio < items[j].ratio)
                swap(&items[i], &items[j]);
}

int main() {
    int n;
    float capacity;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item items[n];

    printf("Enter weight and profit of each item:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d - Weight Profit: ", i + 1);
        scanf("%d %d", &items[i].weight, &items[i].profit);
        items[i].ratio = (float)items[i].profit / items[i].weight;
    }

    printf("Enter capacity of knapsack: ");
    scanf("%f", &capacity);

    clock_t start = clock();

    // Sort by profit-to-weight ratio
    sortItems(items, n);

    float totalProfit = 0.0, used = 0.0;

    printf("\nSelected items (weight taken and profit):\n");

    for (int i = 0; i < n && capacity > 0; i++) {
        if (items[i].weight <= capacity) {
            printf("Item %d: Full (W = %d, P = %d)\n", i + 1, items[i].weight, items[i].profit);
            totalProfit += items[i].profit;
            capacity -= items[i].weight;
        } else {
            float fraction = capacity / items[i].weight;
            printf("Item %d: %.2f fraction (W = %d, P = %d)\n", i + 1, fraction, items[i].weight, items[i].profit);
            totalProfit += items[i].profit * fraction;
            capacity = 0; // knapsack full
        }
    }

    clock_t end = clock();
    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nMaximum Profit = %.2f\n", totalProfit);
    printf("CPU Time = %.6f seconds\n", cpu_time);
    printf("Time Complexity: O(n log n)\n");
    printf("Space Complexity: O(n)\n");

    return 0;
}
