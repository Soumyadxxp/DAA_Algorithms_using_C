#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX 100
#define INF 99999

int dist[MAX][MAX], parent[MAX][MAX];
int n;

void printPath(int u, int v) {
    if (u == v) {
        printf("%d", u);
    } else if (parent[u][v] == -1) {
        printf("No path");
    } else {
        printPath(u, parent[u][v]);
        printf(" -> %d", v);
    }
}

void floydWarshall() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (use 99999 for INF):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
            if (i == j)
                parent[i][j] = i;
            else if (dist[i][j] != INF)
                parent[i][j] = i;
            else
                parent[i][j] = -1;
        }

    clock_t start = clock();
    floydWarshall();
    clock_t end = clock();

    printf("\nShortest distance matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", dist[i][j]);
        }
        printf("\n");
    }

    printf("\nPaths between all pairs:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && dist[i][j] != INF) {
                printf("Path from %d to %d (Cost: %d): ", i, j, dist[i][j]);
                printPath(i, j);
                printf("\n");
            }
        }
    }

    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nCPU Time: %.6f seconds\n", cpu_time);
    printf("Time Complexity: O(V^3)\n");
    printf("Space Complexity: O(V^2)\n");

    return 0;
}
