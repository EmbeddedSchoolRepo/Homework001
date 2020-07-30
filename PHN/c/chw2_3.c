#include <stdio.h>

int main(void)

{
	int x;
	int y;

	printf("X value:\n");
	scanf("%d",&x);

	
	printf("Y value:\n");
	scanf("%d",&y);
	
	if(x > 0 && y > 0)
	{
		printf("Area 1\n");
	}
	else if(x < 0 && y > 0)
	{
		printf("Area2\n");
	}
	else if(x < 0 && y < 0)
	{
		printf("Area 3\n");
	}
	else if(x > 0 && y < 0)
	{
		printf("Area 4\n");
	}
	else
	{
		printf("Invalid Value(except 0)");
	}
	return 0;
}
