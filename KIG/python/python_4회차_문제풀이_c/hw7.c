#include <stdio.h>

int main(void)
{
	int i;
	int N;
	int n1 = 1, n2 = 3;
	int result = n1 + n2; // 초기값
	int temp;

	printf("몇번째 숫자를 알고 싶습니까? ");
	scanf("%d", &N);

	for (i = 3; i < N; i++) {
		temp = result;
		result += n2;
		n2 = temp;
	}

	if(N == 1){
		printf("%d 번째 숫자는 1 입니다.\n", N);	
	}
	else if(N == 2){
		printf("%d 번째 숫자는 3 입니다.\n", N);	
	}	
	else{
		printf("%d 번째 숫자는 %d 입니다\n", N, result);
	}

	return 0;
}
