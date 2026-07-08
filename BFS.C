#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX 100

int visited[MAX];
int graph[MAX][MAX];
int heuristic[MAX];
int nodes;

typedef struct {
    int node;
    int h;
} Node;

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void sort(Node arr[], int size) {
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-i-1; j++) {
            if (arr[j].h > arr[j+1].h) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void greedyBFS(int start, int goal) {
    Node queue[MAX];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = (Node){start, heuristic[start]};

    printf("Greedy BFS Traversal: ");

    while (front < rear) {
        sort(queue + front, rear - front);  // sort the queue based on heuristic

        Node current = queue[front++];
        printf("%d ", current.node);

        if (current.node == goal) {
            printf("\nGoal %d found!\n", goal);
            return;
        }

        for (int i = 0; i < nodes; i++) {
            if (graph[current.node][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = (Node){i, heuristic[i]};
            }
        }
    }

    printf("\nGoal %d not reachable.\n", goal);
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
    greedyBFS(start, goal);
    clock_t end = clock();

    double cpu_time_used = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("CPU Time: %.6f seconds\n", cpu_time_used);

    return 0;
}
//TIME - O(V),O(VlogV+E),O(V^2)
