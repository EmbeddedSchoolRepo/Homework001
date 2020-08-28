//bubble sort
#include <stdio.h>

void swap(int *a, int *b);
void bubble_sort(int parr[],int start, int end);

int main(void)
{
	int i = 0;
	int arr[] = {12,3,4,0,3,3,21,8};

	for(i=0;i<7;i++)
	{	
		printf("%d\n",arr[i]);
	}

	bubble_sort(arr,0,7);
	
	for(i=0;i<7;i++)
	{	
		printf("%d\n",arr[i]);
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

void bubble_sort(int parr[], int start, int end)
{
	int left,left_plus;
	
	left = start;
	left_plus = start +1;

	if(end==1)
	{
		return;
	}

	while(left_plus<end)
	{
		while(parr[left]>parr[left_plus]&&left_plus<end)
		{
			swap(&parr[left],&parr[left_plus]);
		}

			left++;
			left_plus++;
	}
	
	bubble_sort(parr,start,end-1);//재귀
	
}

