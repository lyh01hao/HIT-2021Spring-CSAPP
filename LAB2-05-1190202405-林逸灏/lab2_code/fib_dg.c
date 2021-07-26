#include <stdio.h>
#include <stdlib.h>

int main () {
    int fib[1000];
    fib[0] = 0;
    fib[1] = 1;
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
        printf("fib(%d) is %d \n", i, fib[i]);
    }
    return 0;
}