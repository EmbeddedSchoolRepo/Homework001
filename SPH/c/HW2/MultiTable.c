#include <stdio.h>

int main(void)
{
	int num1,num2;
	num2=1;

	printf("숫자를 입력하세요.\n");
	scanf("%d",&num1);

	printf("\n결과입니다.\n");
LOOP:
	printf("%d * %d = %d\n", num1, num2, num1*num2);
	num2++;

	if(9>=num2)
	{
		goto LOOP;
	}
	else
	{
	}

	return 0;
}
