#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define E 2.71828182845904523536
#define YEAR_CRIME 10

float poisson(float lambda, int x);
int factorial(int n);

int main(void)
{
	float poisson_value = poisson(YEAR_CRIME, 1);

	printf("다음 달에 범죄가 발생하지 않을 확률은 %f%% 입니다\n", 1-poisson_value);

	return 0;
}

float poisson(float lambda, int x)
{
	float poisoon_value = (pow(lambda, x) * pow(E,1/lambda)) / factorial(x);

	return poisoon_value;
}

int factorial(int n)
{
	if (n > 0) {
		return n * factorial(n - 1);
	}
	else
		return 1;
}
