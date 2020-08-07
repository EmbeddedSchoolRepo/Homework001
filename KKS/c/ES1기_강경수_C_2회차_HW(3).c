#include <stdio.h>

int main(void)
{

	int x_value, y_value;

	scanf("%d %d", &x_value, &y_value);

	if(x_value>0&&y_value>0)
	{
		printf("1사분면\n");
	}
	else if(x_value>0&&y_value<0)
	{
		printf("4사분면");
	}
	else if(x_value<0&&y_value>0)
	{
		printf("2사분면");
	}
	else
	{
		printf("3사분면");
	}

	return 0;		
	}
