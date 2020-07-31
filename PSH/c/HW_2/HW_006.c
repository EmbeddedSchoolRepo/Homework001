#include <stdio.h>
int main(void)
{
	int A, B, C;

	scanf("%d",&A);
	scanf("%d",&B);

	C = A * B;	

	while(B)
	{
		printf("%d\r\n", A * (B % 10));
		B /= 10;
	}
	
	printf("%d\r\n", C); 
	return 0;
}
