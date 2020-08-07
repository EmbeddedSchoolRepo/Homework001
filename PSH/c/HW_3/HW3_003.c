/*
 *  int arr[3][3] = {{1,15,4}, {8,10,16},{2,7,20}}에서
 *  최대값을 찾는 함수 만들기
 *  
 *  1. Key : 이중 for문 사용, 배열 포인터 사용 
 *  2. 변수: 최대값 저장 변수 0으로 초기화, for문 돌릴 count 변수 x2
 *           count max는 define으로 정의
 *  3. 최대값 구하는 식을 함수로 만들기(매개변수 const 정의) 
*/

#include <stdio.h>

#define CNT_MAX 3

int Value_Max(const int(*)[3]);

int main(void)
{
	const int arr[3][3] = {
		{1, 15, 4}, 
		{8, 10, 16}, 
		{2, 7, 20}
	};

	printf("MAX VALUE: %d\r\n", Value_Max(arr));	
	
	return 0;
}

int Value_Max(const int(*pArr)[3])
{
	int i, j;
	int max = 0; //낮은 값 설정

	for(i = 0; i < CNT_MAX; i++)
	{
		for(j = 0; j < CNT_MAX; j++)
		{
			if(max < pArr[i][j])	
			{
				max = pArr[i][j];
			}
		}
	}

	return max;
}