#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(void)
{
	int user_num;
	int count = 0;
	srand((unsigned)time(NULL));
	int answer = rand() % 1000000; // 숫자는 100만 이하.

	while (1) {
		printf("숫자를 입력하세요(남은횟수 : %d회) : ", 20-count);
		scanf("%d", &user_num);
		if (user_num == answer) {
			printf("정답입니다!\n");
			break;
		}
		else if(count != 19) {
			printf("틀렸습니다\n");
			if (user_num > answer) {
				printf("DOWN\n");
			}
			else {
				printf("UP\n");
			}
		}
		else {
			printf("20번의기회를 소진하였습니다 게임이 종료됩니다.\n정답은 %d 였습니다\n", answer);
			break;
		}
		count++;
	}
	return 0;
}

