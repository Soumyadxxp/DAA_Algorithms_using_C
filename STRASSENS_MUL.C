#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX 128  // You can increase this based on system limits

void add(int n, int A[][MAX], int B[][MAX], int result[][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] + B[i][j];
}

void subtract(int n, int A[][MAX], int B[][MAX], int result[][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] - B[i][j];
}

void strassen(int n, int A[][MAX], int B[][MAX], int C[][MAX]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int mid = n / 2;
    int A11[MAX][MAX], A12[MAX][MAX], A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX], B21[MAX][MAX], B22[MAX][MAX];
    int M1[MAX][MAX], M2[MAX][MAX], M3[MAX][MAX], M4[MAX][MAX];
    int M5[MAX][MAX], M6[MAX][MAX], M7[MAX][MAX];
    int temp1[MAX][MAX], temp2[MAX][MAX];

    // Dividing matrices into 4 parts
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mid];
            A21[i][j] = A[i + mid][j];
            A22[i][j] = A[i + mid][j + mid];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mid];
            B21[i][j] = B[i + mid][j];
            B22[i][j] = B[i + mid][j + mid];
        }
    }

    // M1 = (A11 + A22) * (B11 + B22)
    add(mid, A11, A22, temp1);
    add(mid, B11, B22, temp2);
    strassen(mid, temp1, temp2, M1);

    // M2 = (A21 + A22) * B11
    add(mid, A21, A22, temp1);
    strassen(mid, temp1, B11, M2);

    // M3 = A11 * (B12 - B22)
    subtract(mid, B12, B22, temp1);
    strassen(mid, A11, temp1, M3);

    // M4 = A22 * (B21 - B11)
    subtract(mid, B21, B11, temp1);
    strassen(mid, A22, temp1, M4);

    // M5 = (A11 + A12) * B22
    add(mid, A11, A12, temp1);
    strassen(mid, temp1, B22, M5);

    // M6 = (A21 - A11) * (B11 + B12)
    subtract(mid, A21, A11, temp1);
    add(mid, B11, B12, temp2);
    strassen(mid, temp1, temp2, M6);

    // M7 = (A12 - A22) * (B21 + B22)
    subtract(mid, A12, A22, temp1);
    add(mid, B21, B22, temp2);
    strassen(mid, temp1, temp2, M7);

    // C11 = M1 + M4 - M5 + M7
    add(mid, M1, M4, temp1);
    subtract(mid, temp1, M5, temp2);
    add(mid, temp2, M7, temp1);
    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++)
            C[i][j] = temp1[i][j];

    // C12 = M3 + M5
    add(mid, M3, M5, temp1);
    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++)
            C[i][j + mid] = temp1[i][j];

    // C21 = M2 + M4
    add(mid, M2, M4, temp1);
    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++)
            C[i + mid][j] = temp1[i][j];

    // C22 = M1 - M2 + M3 + M6
    subtract(mid, M1, M2, temp1);
    add(mid, temp1, M3, temp2);
    add(mid, temp2, M6, temp1);
    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++)
            C[i + mid][j + mid] = temp1[i][j];
}

void printMatrix(int n, int M[][MAX]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%5d ", M[i][j]);
        printf("\n");
    }
}

int nextPowerOfTwo(int n) {
    int power = 1;
    while (power < n) power *= 2;
    return power;
}

int main() {
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int n;

    printf("Enter size of square matrices (e.g. 2, 4, 8...): ");
    scanf("%d", &n);

    int size = nextPowerOfTwo(n);

    printf("Enter elements of Matrix A (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of Matrix B (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    // Pad extra 0s if needed
    for (int i = n; i < size; i++)
        for (int j = 0; j < size; j++)
            A[i][j] = B[i][j] = 0;

    for (int j = n; j < size; j++)
        for (int i = 0; i < size; i++)
            A[i][j] = B[i][j] = 0;

    clock_t start = clock();
    strassen(size, A, B, C);
    clock_t end = clock();

    printf("\nResult Matrix C = A x B:\n");
    for (int i = 0; i < n; i++) {  // only print original size
        for (int j = 0; j < n; j++)
            printf("%5d ", C[i][j]);
        printf("\n");
    }

    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nCPU Time: %.6f seconds\n", cpu_time);

    printf("\nTime Complexity: O(n^log7) ≈ O(n^2.81)\n");
    printf("Space Complexity: O(n^2) for storing temp matrices and result\n");

    return 0;
}
