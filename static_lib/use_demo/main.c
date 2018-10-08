#include <stdio.h>
#include "sum.h"

int main()
{
	int a = 1;
	int b = 2;
	int c = sum(a,b);
	printf("sum(%d,%d)=%d\n", a,b,c);
}
