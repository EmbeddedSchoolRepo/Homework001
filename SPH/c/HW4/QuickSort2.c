#include <stdio.h>
#include <stdlib.h>

#define RowSize 3
#define ColumSize 3

void swap(int *a, int *b);
int partition(int* arr, int left, int right);
void QuickSort(int* arr, int left, int right);
int *ArrayInsert(int (*ArrTmp)[RowSize]);
int QuickMax(int (*ArrTmp)[RowSize], int Row, int Colum);

int main(void)
{
	int arr[3][3] = {{1,15,4}, {8,10,16}, {2,7,20}};
	int Result;

	Result = QuickMax(arr, RowSize, ColumSize);

	printf("\nMax Value = %d\n", Result);

	return 0;
}

void swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int* arr, int left, int right)
{
	int pivot,less, great;

	less = left;
	great = right;
	pivot = arr[right];

	while(less < great)
	{
		if(pivot < arr[less]) 
		{
			if(pivot > arr[great])
			{
				swap(&arr[less], &arr[great]);
			}
			else
			{
				great--;
			}
		}
		else
		{
			less++;
		}
	}

	swap(&arr[right], &arr[great]);

	return great;
}

void QuickSort(int* arr, int left, int right)
{
	int new_right;

	if(left < right)
	{
		new_right = partition(arr, left, right);
		QuickSort(arr, left, new_right-1);
		QuickSort(arr, new_right+1, right);
	}
	else
	{
		return;
	}
}

int *ArrayInsert(int (*ArrTmp)[RowSize]) 
{
	int *Arr= malloc(sizeof(int) * RowSize * ColumSize); 

	for(int i = 0; i < ColumSize * RowSize; i++)
	{
		Arr[i] = *(*ArrTmp+i);
	}

	return Arr;
}

int QuickMax(int (*ArrTmp)[RowSize], int Row, int Colum)
{
	int *Arr;
	int left, right;

	left = Row - Colum;
	right = Row * Colum -1;
	
	Arr = ArrayInsert(ArrTmp);

	printf("Before QuickSort\n");

	for(int i = 0; i < Row * Colum; i++)
	{
		printf("Arr[%d] = %d\n", i, Arr[i]);
	}

	printf("Quick Sort!!\n");

	QuickSort(Arr, left, right);

	for(int i = 0; i < Row * Colum; i++)
	{
		printf("Arr[%d] = %d\n",i, Arr[i]);
	}

	return Arr[right];
}

