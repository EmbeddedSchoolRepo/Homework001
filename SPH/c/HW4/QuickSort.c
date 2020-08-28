#include <stdio.h>

#define MaxSize 5

void swap(int *a, int *b);
int partition(int* arr, int left, int right);
void QuickSort(int* arr, int left, int right);

int main(void)
{
	int arr[5] = {1000, 2, 3, 17, 50};

	printf("Before QuickSort\n");
	for(int j = 0; j < sizeof(arr)/sizeof(int); j++)
	{
		printf("arr[%d] = %d\n", j, arr[j]);
	}

	QuickSort(arr, 0, MaxSize-1);

	printf("After QuickSorting\n");
	for(int j = 0; j < MaxSize; j++)
	{
		printf("arr[%d] = %d\n", j, arr[j]);
	}

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
