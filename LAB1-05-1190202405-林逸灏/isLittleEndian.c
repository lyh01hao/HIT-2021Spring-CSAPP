#include <stdio.h>

int isLittleEndian(){
    short i = 0x0001;
    return((*(char *)&i)? 1: 0);
}
int main() {
    int i = isLittleEndian();
    if (i == 1) {
        printf("This machine is little endian.");
    } else {
        printf("This machine is big endian.");
    }
    return 0;
}