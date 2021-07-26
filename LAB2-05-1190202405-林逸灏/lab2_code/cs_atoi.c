#include <stdio.h>
#include <stdlib.h>

int cs_atoi(char *a) {
    int result = 0;
    for (int i = 0; a[i] != '\0' && a[i] >= '0' && a[i] <= '9'; i++) {
        result = 10 * result + (a[i] - '0');
    }
    return result;
}

int main() {
    char a[] = "8848";
    printf("%d", cs_atoi(a));
    return 0;
}