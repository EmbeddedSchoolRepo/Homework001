#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int random(void);

int main(void)
{
	int com_num = random();
	int user_num;
	srand((unsigned)time(NULL));

	printf("주사위 숫자를 입력하세요 : ");
	scanf("%d", &user_num);

	if ((user_num > 6) && (user_num < 0)) {
		printf("숫자를 잘못 입력하셨습니다\n");
	}
	else if (com_num == user_num) {
		printf("맞추셨습니다!\n");
	}
	else {
		printf("틀렸습니다! 주사위 숫자는 %d 였습니다", com_num);
	}

	return 0;
}

int random(void)
{
	return (rand() % 6 ) + 1;
}
