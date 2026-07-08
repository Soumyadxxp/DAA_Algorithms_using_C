#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

void add(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void divideAndConquerMultiply(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;
    int A11[MAX][MAX], A12[MAX][MAX], A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX], B21[MAX][MAX], B22[MAX][MAX];
    int C11[MAX][MAX], C12[MAX][MAX], C21[MAX][MAX], C22[MAX][MAX];
    int temp1[MAX][MAX], temp2[MAX][MAX];

    // Initialize all submatrices to 0
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }

    // C11 = A11*B11 + A12*B21
    divideAndConquerMultiply(A11, B11, temp1, newSize);
    divideAndConquerMultiply(A12, B21, temp2, newSize);
    add(temp1, temp2, C11, newSize);

    // C12 = A11*B12 + A12*B22
    divideAndConquerMultiply(A11, B12, temp1, newSize);
    divideAndConquerMultiply(A12, B22, temp2, newSize);
    add(temp1, temp2, C12, newSize);

    // C21 = A21*B11 + A22*B21
    divideAndConquerMultiply(A21, B11, temp1, newSize);
    divideAndConquerMultiply(A22, B21, temp2, newSize);
    add(temp1, temp2, C21, newSize);

    // C22 = A21*B12 + A22*B22
    divideAndConquerMultiply(A21, B12, temp1, newSize);
    divideAndConquerMultiply(A22, B22, temp2, newSize);
    add(temp1, temp2, C22, newSize);

    // Combine results into C
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
}

int main() {
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int n;

    printf("Enter matrix size (must be power of 2 and <= %d): ", MAX);
    scanf("%d", &n);

    printf("Enter Matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter Matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    clock_t start = clock();

    divideAndConquerMultiply(A, B, C, n);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Result Matrix C:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%4d ", C[i][j]);
        printf("\n");
    }

    printf("\nCPU Time: %.6f seconds\n", time_spent);

    return 0;
}
