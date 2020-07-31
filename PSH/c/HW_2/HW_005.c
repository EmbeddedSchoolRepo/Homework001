#include <stdio.h>
int main(void)
{
	int N, i, j;

	scanf("%d",&N);

	for(i = 0; i < N; i++)
	{
		for(j = 0; j < i+1; j++)
		{
			printf("*");
		}

		printf("\r\n");
	}
	
	return 0;
}
