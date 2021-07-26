#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;
    float plus_zero, minus_zero, min_positive_float, max_positive_float, min_positive_regular, positive_inf, nan;
    char *x;

    x = (char*)& plus_zero;
	*x = 0b00000000;
	*(x + 1) = 0b00000000;
	*(x + 2) = 0b00000000;
	*(x + 3) = 0b00000000;
	printf("+0：  %f", plus_zero);
	printf("\n");

	x = (char*)& minus_zero;
	*x = 0b00000000;
	*(x + 1) = 0b00000000;
	*(x + 2) = 0b00000000;
	*(x + 3) = 0b10000000;
	printf("-0：  %f", minus_zero);
	printf("\n");

	x = (char*)& min_positive_float;
	*x = 0b00000001;
	*(x + 1) = 0b00000000;
	*(x + 2) = 0b00000000;
	*(x + 3) = 0b00000000;
	printf("最小浮点正数：\t%.50f", min_positive_float);
	printf("\n");

	x = (char*)& max_positive_float;
	*x = 0b11111111;
	*(x + 1) = 0b11111111;
	*(x + 2) = 0b01111111;
	*(x + 3) = 0b01111111;
	printf("最大浮点正数：\t%lf", max_positive_float);
	printf("\n");


	x = (char*)& min_positive_regular;
	*x = 0b00000001;
	*(x + 1) = 0b00000000;
	*(x + 2) = 0b10000000;
	*(x + 3) = 0b00000000;
	printf("最小正规范浮点数：\t%.50f", min_positive_regular);
	printf("\n");


	x = (char*)& positive_inf;
	*x = 0b00000000;
	*(x + 1) = 0b00000000;
	*(x + 2) = 0b10000000;
	*(x + 3) = 0b01111111;
	printf("正无穷大：\t%f", positive_inf);
	printf("\n");


	x = (char*)& nan;
	*x = 0b00000000;
	*(x + 1) = 0b00000000;
	*(x + 2) = 0b11100101;
	*(x + 3) = 0b01111111;
	printf("nan：\t%f", nan);
	printf("\n");
    
    return 0;
}