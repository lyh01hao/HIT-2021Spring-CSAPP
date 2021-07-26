#include <stdlib.h>
#include <stdlib.h>

int fib_recursive (int a) {
    if (a == 0) {
        return 0;
    } else if (a == 1)
    {
        return 1;
    }
    return fib_recursive(a - 1) + fib_recursive(a - 2);
}


int main () {
    int n;
    // scanf("%d", &n);
    for (int i = 1; i <= 5; i++) {
        printf("fib(%d) is %d \n", i, fib_recursive(i));
    }
    fib_recursive(n);
    return 0;
}