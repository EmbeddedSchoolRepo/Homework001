/*
[슬롯머신] 
1,2,3이 랜덤으로 세개의 슬롯에 출력
세 슬롯의 점수가 모두 같다면 2점!
두개만 같다면 1점!
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h> 

void pull_bar(int *arrp,int *cnt); //슬롯머신 바 당기는 함수 

int main(void)
{
	int result_arr[3] = {0,0,0} ;//슬롯머신 출력 숫자 
	int cnt = 0;//중복되는 값을 확인하기위한 변수 

	srand((unsigned int)time(NULL));

	printf("슬롯머신을 시작합니다!\n");
	Sleep(500);
	printf("3\n");
	Sleep(500);
	printf("2\n");
	Sleep(500);
	printf("1\n");
	Sleep(500);

	pull_bar(result_arr,&cnt);
	printf("[%d][%d][%d]\n",result_arr[0],result_arr[1],result_arr[2]);

	switch(cnt)
	{
		case 0:
				printf("꽝!");
				break;
		case 1:
				printf("1점!");
				break;
		case 2:
				printf("2점!");
				break;
		default:
				break;
	}

	return 0;
}

void pull_bar(int *arrp,int *cntp)
{	
	int j = 0;
	int num = 0;
	for(j=0;j<3;j++)
	{
		num=rand()%3+1;
		if(num==*(arrp+(j-1)))
		{
			(*cntp)++;   
		}
		*(arrp+j) = num;
	}
}
