#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PEOPLE 5 // 사람 수
#define WIDTH_LINE 10

int odd_random(void);

int main(void)
{
	int i, j;

	srand((unsigned)time(NULL));
	
	int num[50][50]; //충분히 큰 2차원배열
	char character[50][50]; //충분히 큰 2차원배열
	int random_width_line;

	for (i = 0; i < WIDTH_LINE ; i++){	// 사다리 생성
		random_width_line = odd_random();		
		for (j = 0; j < PEOPLE * 2 - 1; j++) {	

			if (j % 2 == 0) {
				num[i][j] = 1;
			}
			else if(j == random_width_line){		// j가 홀수 일때 -를 랜덤으로 넣어줌.
				character[i][j] = '-';
			}
			else {
				character[i][j] = '0';
			}
		}
	}

	char c = 'A';	// 사람 이름 생성 및 출력 (A 부터)
	for (i = 0; i < PEOPLE; i++) {
		printf("%c ", c);
		c++;
	}
	printf("\n");

	for (i = 0; i < WIDTH_LINE; i++) {	// 사다리 출력
		for (j = 0; j < PEOPLE * 2 - 1; j++) {
			if (j % 2 == 0) {
				printf("%d", num[i][j]);
			}
			else {
				printf("%c", character[i][j]);
			}
		}
		printf("\n");
	}

	int win = rand() % PEOPLE;	//결과 랜덤 출력
	for (i = 0; i < PEOPLE; i++) {
		if (i == win) {
			printf("w "); //w = win
		}
		else {
			printf("f "); // f = fail
		}
	}

	return 0;
}

int odd_random(void) // 홀수만 뽑아내야됨 왜냐면 j가 홀수 일때 '-'를 넣어야되기 때문에.
{
	int odd;
	while (1) {
		odd = rand() % (PEOPLE * 2 - 1);
		if (odd % 2 == 0) {
			continue;
		}
		else
			break;
	}

	return odd;
}
