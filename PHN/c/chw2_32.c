#include <stdio.h>

int main(void)
{

	int x,y,area;

	printf("X value: ");
	scanf("%d",&x);

	
	printf("Y value: ");
	scanf("%d",&y);


	if (x > 0 && y > 0)
	{
		area = 1;
	}
	else if (x < 0 && y > 0)
	{
		area = 2;
	}
	else if (x < 0 && y < 0)
	{
		area = 3;
	}
	else if (x > 0 && y < 0)
	{
		area = 4;
	}

	switch(area)
	{
		case 1:
			printf("1사분면\n");
			break;
		case 2:
			printf("2사분면\n");
			break;
		case 3:
			printf("3사분면\n");
			break;
		case 4: 
			printf("4사분면\n");
			break;
		default:
			printf("Invalid value\n");
			break;
	}
	
	return 0;
}
