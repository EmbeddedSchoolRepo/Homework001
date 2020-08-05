/*
** 0. y = 1/3 x^3 + 4 정적분 계산
** 1. 미소범위
** 2. 순간변화율 계산 
*/

#include <stdio.h>

#define F(x) ((((x)*(x)*(x))/3.0f)+4)

float Slope(int, float);

int main(void)
{
	float dx = 0.0001;
	int a;

	scanf("%d",&a);
	printf("%f\r\n", Slope(a, dx));	

	return 0;
}

float Slope(int a, float dx)
{
	return (F(a+dx) - F(a)) / (float)((a+dx) - a);
}
