#include <stdio.h>

void matrix_multi(int (*a)[2], int (*b)[2], int (*c)[2]);

int main(void)
{
	int arr_a[2][2] = {0,0,0,0};
	int arr_b[2][2] = {0,0,0,0};
	int arr_c[2][2] = {0,0,0,0};
	int (*parr_a)[2];
	int (*parr_b)[2];
	int (*parr_c)[2];
	

	scanf("%d %d %d %d", &arr_a[0][0], &arr_a[0][1], &arr_a[1][0], &arr_a[1][1]);
	scanf("%d %d %d %d", &arr_b[0][0], &arr_b[0][1], &arr_b[1][0], &arr_b[1][1]);
	parr_a = &arr_a[0];
	parr_b = &arr_b[0];
	parr_c = &arr_c[0];

	printf("첫번째2X2 행렬\n%d %d\n%d %d\n\n",arr_a[0][0], arr_a[0][1], arr_a[1][0], arr_a[1][1]);
	printf("두번째2X2 행렬\n%d %d\n%d %d\n\n",arr_b[0][0], arr_b[0][1], arr_b[1][0], arr_b[1][1]);

	matrix_multi(parr_a, parr_b, parr_c);


	printf("결과값2X2 행렬\n%d %d\n%d %d\n\n",arr_c[0][0], arr_c[0][1], arr_c[1][0], arr_c[1][1]);



	return 1;
}

void matrix_multi(int (*a)[2], int (*b)[2], int (*c)[2])
{
	int i = 0;
	int j = 0;
	
	for(i=0; i<2; i++)
	{
		for(j=0; j<2; j++)
			c[i][j] = a[i][0]*b[0][j]+a[i][1]*b[1][j];
	}
}
