#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int index;
    int start;
    int finish;
} Activity;

// Swap for sorting
void swap(Activity *a, Activity *b) {
    Activity temp = *a;
    *a = *b;
    *b = temp;
}

// Sort by finish time
void sortByFinishTime(Activity activities[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (activities[i].finish > activities[j].finish)
                swap(&activities[i], &activities[j]);
}

int main() {
    int n;
    printf("Enter number of activities: ");
    scanf("%d", &n);

    Activity activities[n];

    printf("Enter start and finish times of each activity:\n");
    for (int i = 0; i < n; i++) {
        printf("Activity %d (start finish): ", i + 1);
        scanf("%d %d", &activities[i].start, &activities[i].finish);
        activities[i].index = i + 1;  // Store original index
    }

    clock_t start_time = clock();

    // Step 1: Sort activities by finish time
    sortByFinishTime(activities, n);

    // Step 2: Select activities
    int last_finish = 0;
    int selected[n];
    int count = 0;

    printf("\nSelected Activities (index, start, finish):\n");

    for (int i = 0; i < n; i++) {
        if (activities[i].start >= last_finish) {
            printf("Activity %d (Start: %d, Finish: %d)\n", 
                activities[i].index, activities[i].start, activities[i].finish);
            selected[count++] = activities[i].index;
            last_finish = activities[i].finish;
        }
    }

    clock_t end_time = clock();
    double cpu_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Output vector
    printf("\nSolution Vector (Selected Activity Indexes): ");
    for (int i = 0; i < count; i++) {
        printf("%d ", selected[i]);
    }

    printf("\nTotal Activities Selected: %d\n", count);
    printf("CPU Time: %.6f seconds\n", cpu_time);
    printf("Time Complexity: O(n^2) (for simple sorting), can be O(n log n) with quicksort\n");
    printf("Space Complexity: O(n) (for storing activities and result)\n");

    return 0;
}
