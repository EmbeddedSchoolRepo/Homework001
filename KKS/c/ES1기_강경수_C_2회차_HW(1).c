#include <stdio.h>

	int main(void)
	{
		int A;
		int B;
		int C;
		int value1, value2, value3, value4;

		scanf("%d %d %d",&A,&B,&C);

		value1 = (A+B)%C;
		value2 = ((A%C)+(B%C))%C;
		value3 = (A*B)%C;
		value4 = ((A%C)*(B%C))%C;
		
		printf("%d\n",value1);
		printf("%d\n",value2);
		printf("%d\n",value3);
		printf("%d\n",value4);

		return 0;
	}
