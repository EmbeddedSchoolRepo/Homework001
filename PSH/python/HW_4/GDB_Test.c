#include <stdio.h>

int test(int num)
{
	return 3*num;
}

int main(void)
{
	int res;  
	int num = 3;

	res = test(num);
	printf("res = %d\n", res);

	return 0;
}
