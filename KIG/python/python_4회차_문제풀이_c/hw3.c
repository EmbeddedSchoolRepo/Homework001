#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define SIZE 200

int odd_random(void);						// 랜덤값 만들기
float mean(float* num);					// 평균값
float median(float* num);				// 중간값
float variance(float* num);				// 분산
float standard_deviation(float* num);	// 표준편차
int i, j;

int main(void)
{
	float mean_value;
	float median_value;
	float variance_value;
	float standard_deviation_value;

	float num[SIZE];
	srand((unsigned)time(NULL));

	for (i = 0; i < SIZE; i++) {
		num[i] = odd_random();
		printf("%.0f ", num[i]);
	}
	printf("\n");

	mean_value = mean(num);
	median_value = median(num);
	variance_value = variance(num);
	standard_deviation_value = standard_deviation(num);

	printf("평균은 %f 입니다.\n", mean_value);
	printf("중간값은 %f 입니다.\n", median_value);
	printf("분산은 %f 입니다.\n", variance_value);
	printf("표준편차는 %f 입니다.\n", standard_deviation_value);

	return 0;
}

int odd_random(void) // 랜덤값 만들기
{
	return rand() % 101;
}

float mean(float* num)	// 평균값
{
	float sum = 0.0f;
	for (i = 0; i < SIZE; i++) {
		sum += *(num + i);
	}
	return sum / (float)SIZE;
}

float median(float* num)	// 중간값
{
	float median_value;
	float temp;
	for (i = 0; i < SIZE; i++){	//오름차순 정렬
		for (j = i+1 ; j < SIZE ; j++) {
			if (*(num + i) > * (num + j)) {
				temp = *(num + i);
				*(num + i) = *(num + j);
				*(num + j) = temp;
			}
		}	
	}
	if (SIZE % 2 == 0) {
		median_value = (*(num + SIZE / 2) + *(num + SIZE / 2 - 1)) / 2;
	}
	else {
		median_value = *(num + (SIZE / 2));
	}

	return median_value;
}
float variance(float* num)	// 분산
{
	float sum_dev = 0; // 편차의 제곱의 합
	float mean_value = mean(num); //평균
	float variance_value;

	for (i = 0; i < SIZE; i++) {
		sum_dev += (*(num + i) - mean_value) * (*(num + i) - mean_value);
	}
	variance_value = sum_dev / (float)SIZE; //분산은 편차의 제곱값들의 평균

	return variance_value;
}

float standard_deviation(float* num)	// 표준편차
{
	float variance_value = variance(num);
	return sqrt(variance_value); // 표준편차는 분산의 제곱근
}
