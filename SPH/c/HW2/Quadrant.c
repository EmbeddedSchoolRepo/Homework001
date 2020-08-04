#include <stdio.h>

int main(void)
{
	int x,y;

	printf("x, y값을 입력하세요.\n");
	scanf("%d%d", &x, &y);

	printf("\n결과입니다.\n");

	if(x>0 && y>0)
	{
		printf("1\n");
	}
	else if(x>0 && y<0)
	{
		printf("4\n");
	}
	else if(x<0 && y>0)
	{
		printf("2\n");
	}
	else
	{
		printf("3\n");
	}

	return 0;
}
