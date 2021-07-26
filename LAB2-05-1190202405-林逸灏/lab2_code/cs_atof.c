#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double cs_atof(char *a) {
    double result = 0.0;
    int i = 0;
    for (i = 0; a[i] != '\0' && a[i] >= '0' && a[i] <= '9'; i++) {
        result = 10 * result + (a[i] - '0');
    }
    int counter = 0;
    if (a[i] = '.') {
       for (i = i + 1; a[i] != '\0' && a[i] >= '0' && a[i] <= '9'; i++) {
        result = 10 * result + (a[i] - '0');
        counter++;
    } 
    }
    result = result * pow(10, 0 - counter);
    return result;
}

int main() {
    char a[] = "8848.789";
    printf("%f", cs_atof(a));
    return 0;
}