#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int odd_random(void);

int main(void)
{
	int num[3];
	int i;
	srand((unsigned)time(NULL));

	for (i = 0; i < 3; i++) {
		num[i] = odd_random();
		printf("%d ", num[i]);
	}
	printf("\n");
	if ((num[0] == num[1]) && (num[1] == num[2])) {
		printf("이겼습니다!\n");
	}
	else {
		printf("졌습니다\n");
	}

	return 0;
}

int odd_random(void)
{
	int num;

	num = rand() % 10;

	return num;
}
