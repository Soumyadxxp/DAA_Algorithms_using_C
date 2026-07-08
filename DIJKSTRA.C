#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX 100
#define INF 99999

int dist[MAX], visited[MAX], parent[MAX];
int graph[MAX][MAX];
int n; // number of vertices

int findMinDistance() {
    int min = INF, min_index = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void printPath(int node) {
    if (parent[node] == -1) {
        printf("%d", node);
        return;
    }
    printPath(parent[node]);
    printf(" -> %d", node);
}

void dijkstra(int src) {
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = findMinDistance();
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printf("\nShortest paths from source %d:\n", src);
    for (int i = 0; i < n; i++) {
        if (i == src) continue;
        printf("To %d (Cost: %d): ", i, dist[i]);
        printPath(i);
        printf("\n");
    }
}

int main() {
    int src;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter source node: ");
    scanf("%d", &src);

    clock_t start = clock();
    dijkstra(src);
    clock_t end = clock();

    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nCPU Time: %.6f seconds\n", cpu_time);
    printf("Time Complexity: O(V^2)\n");
    printf("Space Complexity: O(V)\n");

    return 0;
}
