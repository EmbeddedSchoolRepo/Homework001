#include <stdio.h>

int main(void)
{
	int N, cnt;

	scanf("%d", &N);
	
	while(N > 9)
	{
		printf("구구단 should be up to 9\r\n");
		scanf("%d", &N);
	}

	for(cnt = 1; cnt < 10; cnt++)
	{
		printf("%d * %d = %d\r\n", N, cnt, (N * cnt));
	}

	return 0;
}
