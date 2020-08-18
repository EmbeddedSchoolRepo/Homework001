#include <stdio.h>

int main(void)
{
	int i;
	int N = 57;
	long long temp;
	long long n1, n2, result;
	long long sum_even = 0, sum_odd = 0;

	for (i = 1; i < N + 1; i++) {
		if(i == 1){
			n1 = 1;
			sum_odd = n1;
		}
		else if(i == 2){
			n2 = 1;
			sum_odd += n2;
		}
		else if(i == 3){
			result = n1 + n2;
			sum_even = result;
		}
		else{
			temp = result;
			result += n2;
			n2 = temp;

			if(result % 2 == 0){
				sum_even += result;
			}
			else{
				sum_odd += result;
			}
		}
	}

	printf("짝수 합 : %lld\n", sum_even);
	printf("홀수 합 : %lld\n", sum_odd);
	printf("홀수 합 - 짝수 합 : %lld\n", sum_odd - sum_even);

	return 0;
}
