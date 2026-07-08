#include <stdio.h>

int fibonacciIterative(int n) {
    int a = 0, b = 1, temp;
    if (n == 0) return 0;
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

int main() {
    int n;
    printf("Enter term number: ");
    scanf("%d", &n);

    printf("Fibonacci Term [%d] = %d\n", n, fibonacciIterative(n));
    return 0;
}
