#include <stdio.h>
int main(){
    int i = sizeof(int *) * 8;
    printf("%d", i);
    return 0;
}