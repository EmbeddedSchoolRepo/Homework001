#include <stdio.h>

	int main(void)
	{
		int x; 
		int y = 1;
		int multi;

		scanf("%d", &x);
	
		while(y<10)
		{
			multi = x*y;
			printf("%d * %d = %d\n",x, y, multi);
			y++;
		}

		return 0;
	}
