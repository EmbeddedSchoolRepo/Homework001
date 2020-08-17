
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
	int i = 0;
	long long sum_odd = 0;
	long long sum_even = 0;


	long long arr[57] = {1,1,};

	for(i=2;i<57;i++)
	{
		arr[i] = arr[i-1]+arr[i-2];
	}

		for(i=0;i<57;i++)
	{
		printf("arr[%d]:%lli\n",i,arr[i]);
	}
		                      
		for(i=0;i<57;i++)
	{
		if((arr[i]%2)==0)
		{   
			sum_odd +=arr[i];
		}

		else if((arr[i]%2)==1)
		{
			sum_even +=arr[i];
		}
	}
		printf("%lli\n",sum_odd);
		printf("%lli\n",sum_even);

}
