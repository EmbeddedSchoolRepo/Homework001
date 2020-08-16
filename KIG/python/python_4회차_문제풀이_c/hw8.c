#include <stdio.h>
#define N 57
int main(void)
{
	int i;
	long long sum_even = 0;
	long long	sum_odd = 0;
	long long sub;
	long long num[N];
	num[0] = 1;
	num[1] = 1;

	for (i = 2; i < N; i++) {
		num[i] = num[i - 1] + num[i - 2];
	}

	for (i = 0; i < N; i++) {
		if (num[i] % 2 == 0) {
			sum_even += num[i];
		}
		else {
			sum_odd += num[i];
		}
	}
	sub = sum_odd - sum_even;

	printf("홀수들의 합 : %lld\n", sum_odd);
	printf("짝수들의 합 : %lld\n", sum_even);
	printf("홀수합 - 짝수합 : %lld\n", sub);

	return 0;
}
