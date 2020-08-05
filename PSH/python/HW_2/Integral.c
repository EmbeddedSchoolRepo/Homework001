/*
** 0 ~ 3까지 y = x^2 정적분 시행
** i. dx 미소값 결정
** 2. 각 분할된 면적의 누적 합 계산
** 3. 결과 출력
*/

#include <stdio.h>
#include <math.h>

#define F(x) ((x)*(x))

float Integral(int, int, float);

int main(void)
{
	float dx = 0.0001;
	int start, end;

	scanf("%d %d", &start, &end);
	printf("%f", Integral(start, end, dx));

	return 0;
}

float Integral(int start, int end, float dx)
{
	float curX = 0.0f;
	float area = 0.0f;
	int i, loop_cnt;

	loop_cnt = round((end - start) / dx);

	for(i = 0; i < loop_cnt; i++)
	{
		area += (F(curX) * dx);  
		curX += dx;		
	}

	return area;
}


