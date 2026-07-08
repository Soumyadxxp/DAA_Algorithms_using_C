
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

// Structure to represent an edge
typedef struct {
    int src, dest, weight;
} Edge;

Edge edges[MAX];
int parent[MAX];
int n, e;

// Find parent of node (with path compression)
int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

// Union of two subsets
void unionSets(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    parent[rootA] = rootB;
}

// Sort edges by weight
void sortEdges() {
    for (int i = 0; i < e - 1; i++) {
        for (int j = 0; j < e - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

// Kruskal’s algorithm
void kruskal() {
    int totalCost = 0;
    printf("\nEdges in the MST:\n");
    printf("Edge\tWeight\n");

    for (int i = 0; i < e; i++) {
        int u = find(edges[i].src);
        int v = find(edges[i].dest);

        if (u != v) {
            printf("%d - %d\t%d\n", edges[i].src, edges[i].dest, edges[i].weight);
            totalCost += edges[i].weight;
            unionSets(u, v);
        }
    }

    printf("Total Cost of MST: %d\n", totalCost);
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter %d edges (src dest weight):\n", e);
    for (int i = 0; i < e; i++) {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    // Initialize DSU
    for (int i = 0; i < n; i++)
        parent[i] = i;

    sortEdges(); // Sort edges by weight

    // Time measurement
    clock_t start = clock();
    kruskal();
    clock_t end = clock();

    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("CPU Time: %.6f seconds\n", cpu_time);

    printf("\nTime Complexity: O(E log E) [Due to edge sorting]\n");
    printf("Space Complexity: O(V) [DSU array]\n");

    return 0;
}
