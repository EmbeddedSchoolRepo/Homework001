
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
	int i = 0;
	int a = 0;
	int b = 0;

	int arr[23] = {1,3,};

	for(i=2;i<23;i++)
	{
		arr[i] = arr[i-1]+arr[i-2];
	}

		for(i=0;i<23;i++)
	{
		printf("arr[%d]:%d\n",i,arr[i]);
	}
}
