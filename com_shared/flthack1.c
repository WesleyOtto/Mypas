#include <stdio.h>

int i;float x;double xx;

int main()
{
i = 3;
x = 3.14159;
xx = 3.14159;
	i = i + 8;
	x = x + 8;
	xx = xx + 8;
	printf("i=%i, x=%f, xx=%lf\n",i,x,xx);
	return 0;
}

