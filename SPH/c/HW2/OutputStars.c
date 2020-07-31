#include <stdio.h>

int main(void)
{
	int num;
	int cmp1,cmp2;
	cmp1=0;
	cmp2=0;

	printf("숫자를 입력하세요.\n");
	scanf("%d",&num);

	printf("\n결과입니다.\n");
	do
	{
		cmp2=cmp1;
		do
		{
			printf("*");
			cmp2--;
		}while(cmp2>=0);
		printf("\n");
		cmp1++;
	}while(cmp1<num);

	return 0;
}
