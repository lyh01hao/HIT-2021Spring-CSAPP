#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[1000], str_1[1000];
    int n;
    printf("Please input a integer:\n");
    scanf("%d", &n);
    int n_copy = n;
    int a = n % 10;
    for (int i = 0; n_copy != 0; i++) {
        str[i] = n_copy % 10 + '0';
        n_copy = n_copy / 10;
    }
    for (int i = strlen(str) - 1, j = 0; i >= 0; i--, j++) {
        str_1[j] = str[i];
    }
    printf("%s", str_1);
    return 0;
}