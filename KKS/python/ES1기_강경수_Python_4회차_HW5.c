#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
	int ran_num = 0;
	int user_num = 0;
	int i = 0;
	int cnt= 0;

	srand((unsigned int)time(NULL));

	ran_num = rand()%100+1;
	printf("%d\n",ran_num);

	scanf("%d",&user_num);

	for(i=0;i<100;i++)
	{
		if(ran_num>user_num)
		{
			cnt++;
			if(cnt==19)
			{
				printf("패배하였습니다!\n");
				break;
			}
			printf("더 큰수를 입력하세요!\n");
			scanf("%d",&user_num);
		}
	
		else if(ran_num<user_num)
		{
			cnt++;
			if(cnt==19)
			{
				printf("패배하였습니다!\n");
				break;
			}
			printf("더 작은수를 입력하세요!\n");
			scanf("%d",&user_num);
		}

		else 
		{
			printf("정답입니다!\n");
			break;
		}
	}
}
