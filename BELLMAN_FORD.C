#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX 100
#define INF 99999

typedef struct {
    int u, v, w;
} Edge;

Edge edges[MAX];
int dist[MAX], parent[MAX];
int n, e;

void printPath(int node) {
    if (parent[node] == -1) {
        printf("%d", node);
        return;
    }
    printPath(parent[node]);
    printf(" -> %d", node);
}

void bellmanFord(int src) {
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[src] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < e; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    // Check for negative weight cycle
    for (int j = 0; j < e; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("Negative weight cycle detected!\n");
            return;
        }
    }

    // Output
    printf("\nShortest paths from source %d:\n", src);
    for (int i = 0; i < n; i++) {
        if (i == src) continue;
        printf("To %d (Cost: %d): ", i, dist[i]);
        if (dist[i] == INF)
            printf("Unreachable");
        else
            printPath(i);
        printf("\n");
    }
}

int main() {
    int src;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter %d edges (u v w):\n", e);
    for (int i = 0; i < e; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    printf("Enter source node: ");
    scanf("%d", &src);

    clock_t start = clock();
    bellmanFord(src);
    clock_t end = clock();

    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nCPU Time: %.6f seconds\n", cpu_time);
    printf("Time Complexity: O(V * E)\n");
    printf("Space Complexity: O(V)\n");

    return 0;
}
