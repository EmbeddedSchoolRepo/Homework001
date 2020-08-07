#include <stdio.h>
 
int main(void)
{
 
	int a, b, c;
	b = 1;
 
	scanf("%d",&a);
 
	while(b<=a) 
	{
		for( c=1; c<=b; c++)
		{
			printf("★");
		}
		printf("\n");
		b++;
	}
	return 0;
}
 
