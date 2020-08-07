/*
 * 오름차순으로 정렬하기
 * 0.알고리즘 이해: 확실한 이해가 먼저
 * 1.key : 이중 for 문사용, swap 처리 
 * 2.변수 : cnt 변수 i, j: 
 * 3.값이 아닌 Index가 중요하기에  
 */

#include <stdio.h>

void Sort_Selection(int *, const int);
void Swap(int*, int*);
void Print_ArrInt(const int*, const int);

int main(void)
{
    int i;
    int balance[] = {1000, 2, 3, 17, 50};
    const int count = sizeof(balance) / sizeof(int);

    Print_ArrInt(balance, count);
    Sort_Selection(balance, count);
    Print_ArrInt(balance, count);

    return 0;
}

void Sort_Selection(int *pArr, const int count)
{
    int i, j;
    int index_min;     
    for(i = 0; i < (count - 1); i++)
    {
        index_min = i;

        for(j = (i+1); j < count; j++)
        {
            if(pArr[index_min] > pArr[j])
            {
               index_min = j; 
            }
        }

        /* 
        최소값의 인덱스가 변하지 않았으면 
        불필요한 Swap은 낭비
        */
        if(index_min != i)
        {
            Swap(&pArr[i], &pArr[index_min]); 
        }
    }
}

void Swap(int *pValue_1, int *pValue_2)  
{
    int temp;
    temp = *pValue_1;
    *pValue_1 = *pValue_2;
    *pValue_2 = temp;
}

void Print_ArrInt(const int *pArr, const int count)
{
    int i = 0;

    for(i = 0; i < count; i++)
    {
        printf("%d ", pArr[i]);
    }

    printf("\n\r");
}