#include <stdio.h>

int main(void)
{
	int A, B, C;

	scanf("%d %d %d", &A, &B, &C);
	while(C == 0)
	{
		printf("The third number should not be 0\r\n");
		scanf("%d %d %d", &A, &B, &C);
	}

	printf("%d\r\n", (A+B)%C);
	printf("%d\r\n", ((A%C)+(B%C))%C);
	printf("%d\r\n", (A*B)%C);
	printf("%d\r\n", ((A%C)*(B%C))%C);
	
	return 0;
}

