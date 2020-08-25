#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int scan_key(void);

int main(void)
{
	int ran_num = 0;
	int user_num = 0;
	int cnt= 0;

	srand((unsigned int)time(NULL));

	ran_num = rand()%100+1;
	printf("%d\n",ran_num);

	while(cnt<19)
	{
		user_num = scan_key();
		if(ran_num>user_num)
		{
			printf("더 큰값을 입력하세요\n");
		}

		if(ran_num<user_num)
		{
			printf("더 작은값을 입력하세요\n");
		}

		if(ran_num==user_num)
		{
			printf("정답입니다!\n");
			break;
		}

		cnt++;

		if(cnt==19)
		{
			break;
		}
	}
	return 0;
}


int scan_key(void)
{
	int num = 0;
	
	while(1)
	{
		scanf("%d",&num);
		if(getchar()!='\n')
		{
			printf("양의 정수만을 입력하세요!\n");
		}
		else
		{
			return num;
		}
	}
}
