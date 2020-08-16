#include <stdio.h>
#define N 100

int main(void)
{
	int i;
	int num[N];
	int n;
	num[0] = 1; // 초깃값
	num[1] = 3;	// 초깃값

	for (i = 2; i < N; i++) {
		num[i] = num[i - 1] + num[i - 2];
	}
	printf("몇번째 숫자를 알고 싶습니까? ");
	scanf("%d", &n);
	printf("%d 번째 숫자는 %d 입니다\n", n, num[n-1]);


	return 0;
}
