#include <stdio.h>

int main(void)
{
	int n;
	int cnt = 1;

	printf("구구단 몇단을 출력하시겠습니까?");
        scanf("%d",&n);
	
	do
	{
		printf("%d * %d = %d \n", n, cnt, n*cnt);
		cnt++;	
	}while(cnt<10);
	
	return 0;
}
