#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX 100

int visited[MAX];
int graph[MAX][MAX];
int heuristic[MAX];
int path[MAX];
int pathIndex = 0;
int nodes;

void greedyDFS(int current, int goal) {
    visited[current] = 1;
    path[pathIndex++] = current;

    if (current == goal)
        return;

    // Find the unvisited neighbor with the lowest heuristic
    int nextNode = -1;
    int minHeuristic = INT_MAX;

    for (int i = 0; i < nodes; i++) {
        if (graph[current][i] && !visited[i]) {
            if (heuristic[i] < minHeuristic) {
                minHeuristic = heuristic[i];
                nextNode = i;
            }
        }
    }

    if (nextNode != -1) {
        greedyDFS(nextNode, goal);
    }
}

int main() {
    int start, goal;

    printf("Enter number of nodes: ");
    scanf("%d", &nodes);

    printf("Enter adjacency matrix (%d x %d):\n", nodes, nodes);
    for (int i = 0; i < nodes; i++)
        for (int j = 0; j < nodes; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter heuristic values for each node:\n");
    for (int i = 0; i < nodes; i++)
        scanf("%d", &heuristic[i]);

    printf("Enter start node: ");
    scanf("%d", &start);

    printf("Enter goal node: ");
    scanf("%d", &goal);

    clock_t begin = clock();
    greedyDFS(start, goal);
    clock_t end = clock();

    printf("\nGreedy DFS Traversal Path: ");
    for (int i = 0; i < pathIndex; i++) {
        printf("%d ", path[i]);
    }

    if (path[pathIndex - 1] == goal) {
        printf("\nGoal %d found!\n", goal);
    } else {
        printf("\nGoal %d not reachable.\n", goal);
    }

    double cpu_time_used = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("CPU Time: %.6f seconds\n", cpu_time_used);

    return 0;
}
