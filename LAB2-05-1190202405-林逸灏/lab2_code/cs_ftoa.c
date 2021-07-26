#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char str[1000], str_1[1000];
    double dn;
    printf("Please input a float number:\n");
    scanf("%lf", &dn);
    double dn_copy = dn;

    int keta = 0;
    while(dn_copy - (long)dn_copy != 0) {
        dn_copy = dn_copy * 10;
        keta++;
    }
    long n_copy = (long)dn_copy;

    for (int i = 0; n_copy != 0; i++) {
        str[i] = n_copy % 10 + '0';
        n_copy = n_copy / 10;
    }
    int dot = strlen(str) - keta;
    int ii = strlen(str) - 1, jj = 0;
    for (; ii >= 0, jj < dot; ii--, jj++) {
        str_1[jj] = str[ii];
    }
    str_1[dot] = '.';
    for (; ii >= 0; ii--, jj++) {
        str_1[jj + 1] = str[ii];
    }

    // printf("%s\n", str);
    printf("%s\n", str_1);
    return 0;
}