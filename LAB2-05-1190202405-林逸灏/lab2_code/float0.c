#include <stdio.h>
#include <stdlib.h>

int main () {
    float i = 10.124;
    float tiny = 0.000000000000000000000000005460000000000000000000000000000000000000546;
    printf("除以正0：%f\n", i/+0.0);
    printf("除以负0：%f\n", i/-0.0);
    printf("除以极小浮点数：%f\n", i/tiny);

    return 0;
}