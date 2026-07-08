#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX 100
#define INF 99999

int parent[MAX];     // To store MST
int key[MAX];        // Key values used to pick minimum weight edge
int mstSet[MAX];     // To represent set of vertices included in MST

int minKey(int key[], int mstSet[], int n) {
    int min = INF, min_index;

    for (int v = 0; v < n; v++)
        if (!mstSet[v] && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void printMST(int parent[], int graph[MAX][MAX], int n) {
    int totalCost = 0;
    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++) {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
        totalCost += graph[i][parent[i]];
    }
    printf("Total cost of MST: %d\n", totalCost);
}

void primMST(int graph[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = 0;
    }

    key[0] = 0;      // Start from first vertex
    parent[0] = -1;  // First node is root

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, n);
}

int main() {
    int n, graph[MAX][MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    clock_t start = clock();
    primMST(graph, n);
    clock_t end = clock();

    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("CPU Time: %.6f seconds\n", cpu_time);

    // Complexity
    printf("\nTime Complexity: O(V^2)\n");
    printf("Space Complexity: O(V)\n");

    return 0;
}
