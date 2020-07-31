#include <stdio.h>

int main(void)
{
	int num1,num2;
	int tmp;

	printf("세 자리수를  입력하세요.\n");
	scanf("%d%d", &num1, &num2);
	tmp=num2;

	printf("\n결과입니다.\n");

	for(int i=0; i<3; i++)
	{
		printf("%d\n", num1*(tmp%10));
		tmp=tmp/10;
	}
	printf("%d\n", num1*num2);


	return 0;
}
