#include <stdio.h>

int binomialRecursive(int n, int k) {
    if (k == 0 || k == n)
        return 1;
    return binomialRecursive(n - 1, k - 1) + binomialRecursive(n - 1, k);
}

int main() {
    int n, k;
    printf("Enter n and k: ");
    scanf("%d %d", &n, &k);
    printf("Binomial Coefficient C(%d, %d) = %d\n", n, k, binomialRecursive(n, k));
    return 0;
}
