#include <stdio.h>

int main(void)
{
	int a,b,c;

	printf("A: ");
	scanf("%d",&a);
	printf("B: ");
	scanf("%d",&b);
	printf("C: ");
	scanf("%d",&c);

	printf("(A+B)%%C = %d\n",(a+b)%c);
	printf("((A%%C)+(B%%C))%%C = %d\n",((a%c)+(b%c))%c);	
	printf("(A*B)%%C = %d\n",(a*b)%c);
	printf("((A%%C)*(B%%C))%%C = %d\n",((a%c)*(b%c))%c);	

}
