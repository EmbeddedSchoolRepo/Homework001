#include <stdio.h>
#define N 2

void multiply()
{
	int result[N][N];
	int arr1[N][N] = {{1,2}, {3,4}};
	int arr2[N][N] = {{1,2}, {3,4}};
	
	int i, j;
	
	for( i = 0; i < N ; i++){
		for(j = 0 ; j < N ; j++){
			result[i][j] = (arr1[i][j] * arr2[i][j]);
			printf("%d ",result[i][j]);
		}		
	}
}

void main(void){

	printf("start 2 by 2 multiply: \n");
	multiply();
	
}
	
