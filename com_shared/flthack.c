#include <stdio.h>

int i = 3;

float x = 3.14159;

double xx = 3.14159;

int main()
{
	i = i + 8;
	x = x + 8;
	xx = xx + 8;
	printf("i=%i, x=%f, xx=%lf\n",i,x,xx);
	return 0;
}

