#include <stdio.h>

void AscendingSort(int* ArrTmp, int size); 

int main(void)
{
	int balance[] = {1000, 2, 3, 0, 9};

	printf("Before Sorting\n");

	for(int i = 0; i < sizeof(balance)/sizeof(int); i++)
	{
		printf("balance[%d] = %d\n", i, balance[i]);
	}

	AscendingSort(balance, sizeof(balance)/sizeof(int));

	printf("After Sorting\n");

	for(int i = 0; i < sizeof(balance)/sizeof(int); i++)
	{
		printf("balance[%d] = %d\n", i, balance[i]);
	}
	
	return 0;
}

void AscendingSort(int* ArrTmp, int size)
{
	int tmp;

	for(int i = 4; i>=0; i--)
	{
		for(int j = 0; j < i; j++)
		{
			if(ArrTmp[i] < ArrTmp[j])
			{
				tmp = ArrTmp[i];
				ArrTmp[i] = ArrTmp[j];
				ArrTmp[j] = tmp;
			}
			else
			{
				ArrTmp[i] = ArrTmp[i];
			}
		}
	}
}

