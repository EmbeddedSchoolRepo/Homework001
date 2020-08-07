#include <stdio.h>

void function_max(int (*arr)[3], int *value);

int main(void)
{
	int arr_a[3][3];
	int i = 0;
	int j = 0;
	int max_value = 0;

	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			scanf("%d",&arr_a[i][j]);
		}
	}

	function_max(arr_a, &max_value);

	printf("%d ",max_value);

	return 0;
}

void function_max(int (*arr)[3], int *value)
{

	int k = 0;
	int l = 0;

	for(k=0;k<3;k++)
	{
		for(l=0;l<3;l++)
		{	
			if(*(*(arr+k)+l)>(*value))
			{
				*value = *(*(arr+k)+l);
			}
			
		}

	}	
}

