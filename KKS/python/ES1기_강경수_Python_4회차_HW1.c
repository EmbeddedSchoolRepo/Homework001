#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int random_dice(void);

int main(void)
{
	int i = 0;
	int dice_num = 0;
	int user_num = 0;
	srand((unsigned int)time(NULL)); 
	
	do
	{
		printf("1~6사이의 범위를 입력하세요!");
		printf("주사위 숫자를 입력하세요 범위 1~6\n");
		scanf("%d",&user_num);
	} while(user_num>6||user_num<1);
	
	
	dice_num = random_dice();
	printf("주사위 값은!" "%d\n",dice_num);
	
	if(dice_num==user_num)
	{
		printf("승리!\n");
	}
	else
	{
		printf("패배!\n");
	}

	return 0;
}

int random_dice()
{	
	int i = 0;
	int dice_numf=0;

	dice_numf = rand()%6+1;
	return dice_numf;
}
