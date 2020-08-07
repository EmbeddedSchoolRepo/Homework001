#include <stdio.h>

void ascend_order(int *a);

int main(void)
{

	int arr_a[6] = {1, 55, 200, 37, 66, 21};
	int j = 0;

	ascend_order(&arr_a[0]);
	
	for(j=0;j<6;j++)
	{
		printf("%d\n",arr_a[j]);
	}
	
	return 0;
}

//함수의 컨셉
//가장 처음부터 
void ascend_order(int *a)
{
	int temp_arr[6];
	int temp = 0;
	int i = 0;
	int j = 0;

	for(i=0;i<6;i++)
	{
		if(*(a+i)>temp)
		{
			temp = *(a+i);
			temp_arr[0] = temp;
		}
	}

	for(j=0;j<6;j++)
	{
		temp = 0;
		for(i=0;i<6;i++)
		{
			if(temp_arr[j]>(*(a+i))&&(*(a+i))>temp)
			{
				temp = *(a+i);
				temp_arr[j+1] = temp;
			}
		}
	}

	/*
	temp = 0;	
	for(i=0;i<6;i++)
	{
		if(temp_arr[0]>(*(a+i))&&(*(a+i))>temp)
		{
			temp = *(a+i);
			temp_arr[1] = temp;
		}
	}
	
	temp = 0;
	for(i=0;i<6;i++)
	{
		if(temp_arr[1]>(*(a+i))&&(*(a+i))>temp)
		{
			temp = *(a+i);
			temp_arr[2] = temp;
		}
	}
	
	temp = 0;
	for(i=0;i<6;i++)
	{
		if(temp_arr[2]>(*(a+i))&&(*(a+i))>temp)
		{
			temp = *(a+i);
			temp_arr[3] = temp;
		}
	}

	temp = 0;
	for(i=0;i<6;i++)
	{
		if(temp_arr[3]>(*(a+i))&&(*(a+i))>temp)
		{
			temp = *(a+i);
			temp_arr[4] = temp;
		}
	}
	
	temp = 0;
	for(i=0;i<6;i++)
	{
		if(temp_arr[4]>(*(a+i))&&(*(a+i))>temp)
		{
			temp = *(a+i);
			temp_arr[5] = temp;
		}
	}
	*/

	for(i=0;i<6;i++)
	{
		*(a+i)=temp_arr[i];
	}

}

