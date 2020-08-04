#include <stdio.h>
#include <math.h>

float func(float currX)
{
	return currX * currX; //함수식 y = x^2
}
float differential(float pnt, float dx)
{
 	float linear = 0;
	linear = (func(pnt + dx) - func(pnt)) / dx; //미분공식  f(a+dx)-f(a) / dx를 사용. a점의 기울기를 구하고 싶음.
	return linear;
}

int main(void) 
{

	float a = 3;
	float curX = 0;
	float dx = 0.0001; //a+dx지점에서 a지점으로 계속 수렴하게 하기위한 미소값(적정값 설정)
	float result = 0;

	result = differential(a, dx); //함수 사용하여 a점의 기울기를 구하기 위해 a값과 미소값 적용

	printf("integral results: %f\n", result); //5.998611결과 값이 나옴

	return 0;
}

