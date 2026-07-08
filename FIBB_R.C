#include <stdio.h>

int fibonacciRecursive(int n) {
    if (n <= 1)
        return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int main() {
    int n;
    printf("Enter term number: ");
    scanf("%d", &n);

    printf("Fibonacci Term [%d] = %d\n", n, fibonacciRecursive(n));
    return 0;
}
