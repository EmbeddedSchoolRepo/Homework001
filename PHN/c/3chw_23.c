#include <stdio.h>
#define N 3

int MAX(int arr[][N])
{
	int i, j;
	for(i = 0; i<N; i++){
		for(j=0;j<N ; j++){
			if (arr[0][0] < arr[i][j]){
			arr[0][0] = arr[i][j];
			}
		}
	}
	return arr[0][0];
}


void main(void)
{
	int arr[N][N] = {{1, 5, 4}, {8, 10, 16}, {2, 7, 20}};
	int max_value;

	max_value  =  MAX(arr);
	printf("MAX: %d\n", max_value);
}
