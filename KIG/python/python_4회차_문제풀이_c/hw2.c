#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random_num(void);

int main(void)
{
	char slot[6][10] = {"apple", "banana", "kiwi", "cherry", "mango", '7'};
	int i;
	int temp;
	srand((unsigned)time(NULL));

	int win_location[3];

	//정답생성
	for(i = 0 ; i < 3 ; i++){	
		win_location[i] = random_num();
	}
	//정답출력	
	for(i = 0 ; i < 3 ; i++){	
		temp = win_location[i];
		printf("%s ", slot[temp]);
	}
	printf("\n");

	//결과출력	
	if(win_location[0] == win_location[1] && win_location[1] == win_location[2])
	{
		printf("승리!\n");
	}
	else{
		printf("패배\n");
	}

	return 0;
}

int random_num(void)
{
	return rand() % 6;
}


