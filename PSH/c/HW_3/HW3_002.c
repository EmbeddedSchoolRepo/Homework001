/*
 * 2x2 행렬 곱셈 구하기
 * scanf로 배열에 for문 써서 인자들을 받을 것 
 * 규칙을 찾을 것 (3중 for문 사용가능한 규칙 발견)
 * 반복적인 수식은 함수형태로 정리할 것
 */
#include <stdio.h>

#define ROW 2
#define COLUMN 2

void Scanf_Matrix(int(*)[COLUMN]);
void Printf_Matrix(int(*)[COLUMN]);
void Matrix_Mul(int(*)[COLUMN], int(*)[COLUMN], int(*)[COLUMN]); 

int main(void)
{
    int A[ROW][COLUMN] = {0,};
    int B[ROW][COLUMN] = {0,};
    int result[ROW][COLUMN] = {0,};

    Scanf_Matrix(A);
    Scanf_Matrix(B);

    Matrix_Mul(result, A, B);

    Printf_Matrix(A);
    Printf_Matrix(B);
    Printf_Matrix(result);

    return 0;
}

void Scanf_Matrix(int (*pMatrix)[COLUMN])
{
    int i,j;
    int temp;

    for(i = 0; i < COLUMN; i++)
    {
        for(j = 0; j < COLUMN; j++)
        {
            scanf("%d", &temp);
            pMatrix[i][j] = temp;
        }
    }
}

void Matrix_Mul(int(*result)[COLUMN], int(*A)[COLUMN], int(*B)[COLUMN])
{
    int i,j,k;

    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COLUMN; j++)
        {
            for(k = 0; k < COLUMN; k++)
            {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void Printf_Matrix(int(*pMatrix)[COLUMN])
{
    int i,j;

    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COLUMN; j++)
        {
            printf("%d ", pMatrix[i][j]);
        }

        printf("\n");
    }
    printf("\n");
}