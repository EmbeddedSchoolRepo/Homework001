#include <stdio.h>

void MatrixMult(int (*MatrixTmp1)[2], int (*MatrixTmp2)[2], int (*Result)[2]);

int main(void)
{
	int Matrix1[2][2];
	int Matrix2[2][2];
	int ResMatrix[2][2];
	char tmp;

	printf("2x2 행렬1의 요소를 입력하세요.\n");
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<2; j++)
		{
			scanf("%d", &Matrix1[i][j]);
			tmp = getchar();
		}
	}

	printf("\n2x2 행렬2의 요소를 입력하세요.\n");
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<2; j++)
		{
			scanf("%d", &Matrix2[i][j]);
			tmp = getchar();
		}
	}

	printf("\nMatrix1 = \n");
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<2; j++)
		{
			printf("%d\t", Matrix1[i][j]);
		}
		printf("\n");
	}

	printf("\nMatrix2 = \n");
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<2; j++)
		{
			printf("%d\t", Matrix2[i][j]);
		}
		printf("\n");
	}

	MatrixMult(Matrix1, Matrix2, ResMatrix);

	printf("\nResult =\n");
	for(int i = 0; i<2; i++)
	{
		for(int j = 0; j<2; j++)
		{
			printf("%d\t", ResMatrix[i][j]);
		}
		printf("\n");
	}

	return 0;
}	

void MatrixMult(int (*MatrixTmp1)[2], int (*MatrixTmp2)[2], int (*Result)[2])
{
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<2; j++)
		{
			Result[i][j] = MatrixTmp1[i][0]*MatrixTmp2[0][j] + MatrixTmp1[i][1]*MatrixTmp2[1][j];
		}
	}

}
