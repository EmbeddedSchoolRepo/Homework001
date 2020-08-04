#include <stdio.h>

int main(void)
{
	int i,j;
	int n;
	printf("별 몇층을 쌓을것입니까?");
	scanf("%d",&n);

	for(j = 1 ; j <= n ; j++)
	{	
		for (i = 1 ; i <= j ; i++)
		{
			printf("*");
		}
		printf("\n");
	}
	return 0;
}

