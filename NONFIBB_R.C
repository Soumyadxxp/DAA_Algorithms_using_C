#include <stdio.h>

int isFibonacci(int n, int a, int b) {
    if (b > n) return 0;
    if (b == n) return 1;
    return isFibonacci(n, b, a + b);
}

void printNonFibonacciRecursive(int count, int current, int printed) {
    if (printed == count)
        return;

    if (!isFibonacci(current, 0, 1)) {
        printf("%d ", current);
        printNonFibonacciRecursive(count, current + 1, printed + 1);
    } else {
        printNonFibonacciRecursive(count, current + 1, printed);
    }
}

int main() {
    int count;
    printf("How many non-Fibonacci numbers to print: ");
    scanf("%d", &count);

    printf("Non-Fibonacci numbers: ");
    printNonFibonacciRecursive(count, 1, 0);

    return 0;
}
