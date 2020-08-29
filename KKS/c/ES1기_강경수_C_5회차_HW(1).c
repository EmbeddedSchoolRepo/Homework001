#include <stdio.h>

int swap(int *a, int *b);
void quick_sort(int *parr,int start,int end);

int main(void)
{
	int size; //array 크기
	int i; //for 문 변수

	int	arr[] = {3,1,9,5,4,0,22,13,18};
	size = sizeof(arr)/sizeof(arr[0]); //sizeof(arr[])하면 오류나는 이유가?
	
	for(i=0;i<size;i++)
	{
		printf("%d\n",arr[i]);
	}

	quick_sort(arr,0,size);

	for(i=0;i<size;i++)
	{
		printf("쏘트완료%d\n",arr[i]);
	}
	
	return 0;
	
}

int swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void quick_sort(int *parr,int start, int end)
{
	int left,right,pivot;

	right = end;
	left  = start;
	pivot = end;

	if(left>=right)
	{
		return;
	}

	while(right>left) //right와 Left가 교차하는 순간까지 right left값을 서칭하며 ++ --
	{
		while(parr[left]<parr[pivot] && right>left)
		{
			left++;
		}
	
		while(parr[right]>=parr[pivot] && right>left)
		{
			right--;
		}

		swap(&parr[left],&parr[right]); // Pivot 보다 큰 Left를 pivot보다 작은 right자리에서 서로 swap		
	}

	swap(&parr[pivot],&parr[left]);
	
	quick_sort(parr,start,left-1);
	quick_sort(parr,left+1,end);
}

	


