#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

typedef struct {
    char id[10];
    int deadline;
    int profit;
} Job;

void swap(Job* a, Job* b) {
    Job temp = *a;
    *a = *b;
    *b = temp;
}

int compare(const void* a, const void* b) {
    return ((Job*)b)->profit - ((Job*)a)->profit;
}

int main() {
    int n;
    Job jobs[MAX];
    int slot[MAX]; // 1 if occupied, 0 if free
    char result[MAX][10]; // stores selected job IDs
    int maxDeadline = 0;
    int totalProfit = 0;
    int jobCount = 0;

    printf("Enter number of jobs: ");
    scanf("%d", &n);

    printf("Enter job id, deadline and profit for each job:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }

    clock_t start = clock();

    // Sort jobs by profit
    qsort(jobs, n, sizeof(Job), compare);

    printf("\nSorted Jobs by Profit (High → Low):\n");
    for (int i = 0; i < n; i++)
        printf("Job: %s, Deadline: %d, Profit: %d\n", jobs[i].id, jobs[i].deadline, jobs[i].profit);

    // Initialize slots to free
    for (int i = 0; i <= maxDeadline; i++) {
        slot[i] = 0;
        strcpy(result[i], "");
    }

    // Greedy job selection
    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == 0) {
                slot[j] = 1;
                strcpy(result[j], jobs[i].id);
                totalProfit += jobs[i].profit;
                jobCount++;
                break;
            }
        }
    }

    clock_t end = clock();

    // Output
    printf("\nSelected Jobs (Path):\n");
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i])
            printf("Slot %d: %s\n", i, result[i]);
    }

    printf("\nSelected Job Order (Vector): ");
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i])
            printf("%s ", result[i]);
    }

    printf("\n\nTotal Profit: %d\n", totalProfit);
    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("CPU Time: %.6f seconds\n", cpu_time);

    printf("Time Complexity: O(n log n + n * d)\n");
    printf("Space Complexity: O(n + d)\n");

    return 0;
}
