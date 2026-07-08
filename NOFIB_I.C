#include <stdio.h>

int isFibonacci(int n) {
    int a = 0, b = 1, temp;
    while (b < n) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return (b == n || n == 0);
}

int main() {
    int count, i = 1, printed = 0;

    printf("How many non-Fibonacci numbers to print: ");
    scanf("%d", &count);

    printf("Non-Fibonacci numbers: ");
    while (printed < count) {
        if (!isFibonacci(i)) {
            printf("%d ", i);
            printed++;
        }
        i++;
    }

    return 0;
}
