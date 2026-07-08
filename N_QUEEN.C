#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

int board[MAX][MAX];
int N;
int solutionCount = 0;

void printBoard() {
    printf("\nSolution %d:\n", ++solutionCount);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i][j] ? 'Q' : '.');
        }
        printf("\n");
    }

    printf("Queen Positions (row, col): ");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j])
                printf("(%d,%d) ", i + 1, j + 1);
        }
    }
    printf("\n");
}

int isSafe(int row, int col) {
    for (int i = 0; i < col; i++)
        if (board[row][i])
            return 0;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;

    for (int i = row, j = col; i < N && j >= 0; i++, j--)
        if (board[i][j])
            return 0;

    return 1;
}

void solveNQueens(int col) {
    if (col >= N) {
        printBoard();
        return;
    }

    for (int i = 0; i < N; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1;

            printf("\nPlacing queen at (%d,%d):\n", i + 1, col + 1);
            for (int a = 0; a < N; a++) {
                for (int b = 0; b < N; b++) {
                    printf("%c ", board[a][b] ? 'Q' : '.');
                }
                printf("\n");
            }

            solveNQueens(col + 1);
            board[i][col] = 0;  // backtrack
        }
    }
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    printf("Enter the value of N for N-Queen: ");
    scanf("%d", &N);

    if (N < 1 || N > MAX) {
        printf("Invalid N (1 ≤ N ≤ %d)\n", MAX);
        return 1;
    }

    start = clock();
    solveNQueens(0);
    end = clock();

    if (solutionCount == 0) {
        printf("\nNo solution exists for N = %d\n", N);
    }

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTotal CPU Time: %.6f seconds\n", cpu_time_used);

    printf("\nTime Complexity: O(N!) — exponential due to permutations\n");
    printf("Space Complexity: O(N^2) — for board representation\n");

    return 0;
}
