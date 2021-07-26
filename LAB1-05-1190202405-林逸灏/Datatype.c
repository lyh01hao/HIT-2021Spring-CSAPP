#include <stdio.h>
int a = 1;
short b = 2;
long c = 3;
char d = 'd';
float e = 2.718281828;
double f = 2.718281828459;

int array[2] = {0, 1};
typedef struct sss{
    int value;
}s;
s ss;
typedef union uuu{
    char key;
    int value;
}u;
u uu;
enum grades {aa = 1, bb = 2, cc = 3, dd = 4}grade;

int main() {
    ss.value = 1213;
    uu.key = 'a';
    uu.value = 159;
    printf("type\t\t\t\t\tname\t\t\t\t\tvalue\t\t\t\t\taddress\t\t\t\t\thexadecimal\n");
    printf("int\t\t\t\t\ta\t\t\t\t\t%d\t\t\t\t\t%p\t\t\t\t\t%x\n", a, &a, a);
    printf("short\t\t\t\t\tb\t\t\t\t\t%d\t\t\t\t\t%p\t\t\t\t\t%x\n", b, &b, b);
    printf("long\t\t\t\t\tc\t\t\t\t\t%d\t\t\t\t\t%p\t\t\t\t\t%x\n", c, &c, c);
    printf("char\t\t\t\t\td\t\t\t\t\t%c\t\t\t\t\t%p\t\t\t\t\t%x\n", d, &d, d);
    printf("float\t\t\t\t\te\t\t\t\t\t%f\t\t\t\t\t%p\t\t\t\t\t%x\n", e, &e, e);
    printf("double\t\t\t\t\tf\t\t\t\t\t%lf\t\t\t\t\t%p\t\t\t\t\t%x\n", f, &f, f);
    printf("struct\t\t\t\t\tss.value\t\t\t\t\t%d\t\t\t\t\t%p\t\t\t\t\t%x\n", ss.value, &ss, ss.value);
    printf("union\t\t\t\t\tuu.key\t\t\t\t\t%c\t\t\t\t\t%p\t\t\t\t\t%x\n", uu.key, &uu.key, uu.key);
    printf("union\t\t\t\t\tuu.value\t\t\t\t\t%d\t\t\t\t\t%p\t\t\t\t\t%x\n", uu.value, &uu.value, uu.value);
    printf("array\t\t\t\t\tarray[0]\t\t\t\t\t%d\t\t\t\t\t%p\t\t\t\t\t%x\n", array[0], array, array[0]);
    grade = aa;
    printf("enum grades\t\t\t\t\taa\t\t\t\t\t%d\t\t\t\t\t%p\t\t\t\t\t%x\n", grade, &grade, grade);
    printf("main's address = %lx\n", (long)main);
    printf("printf's address = %lx\n", (long)printf);
    return 0;
}