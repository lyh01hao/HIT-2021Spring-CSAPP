#include <stdio.h>
static int utf8len(const char *s)
{
    int i = 0, j = 0;
    while (s[i])
    {
    	//if ((s[i] & 0b11000000) != 0b10000000) j++;
        if ((s[i] & 0xc0) != 0x80) j++;
        i++;
    }
    return j;
}
int main() {
    int word = 0;
	char str[1000], *p;
	printf("输入一个字符串：");
	gets(str);
	p = str;
	word = utf8len(p);
	printf("\t%d", word);
	return 0;
}