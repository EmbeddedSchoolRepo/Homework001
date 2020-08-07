#include <stdio.h>

int MaxVal(int (*ArrTmp)[3]);

int main(void)
{
	int arr[3][3] = {{1, 15, 4}, {8, 10, 16}, {2, 7, 20}};
	int MaxValue;

	MaxValue = MaxVal(arr);

	printf("MaxValue = %d\n", MaxValue);

	return 0;
}

int MaxVal(int (*ArrTmp)[3])
{
	int MaxValue;

	MaxValue = ArrTmp[0][0];

	for(int i = 0; i < 3; i++)
	{
		for(int j = 1; j < 3; j++)
		{
			if(MaxValue < ArrTmp[i][j])
			{
				MaxValue =  ArrTmp[i][j];
			}
			else
			{
				MaxValue = MaxValue;
			}
		}
		printf("%d result = %d\n", i, MaxValue);
	}

	return MaxValue;

}
