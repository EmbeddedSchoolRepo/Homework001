#include <stdio.h>

int main(void)
{
	int A,B,C;

	printf("숫자 3개를 입력하세요.\n");
	scanf("%d%d%d", &A,&B,&C);

	printf("\n결과입니다.\n");
	printf("(A+B)%%C = %d\n", (A+B)%C);
	printf("((A%%C)+(B%%C))%%C = %d\n", ((A%C)+(B%C))%C);
	printf("(A*B)%%C) = %d\n", (A*B)%C);
	printf("((A%%C)*(B%%C))%%C = %d\n", ((A%C)*(B%C))%C);

	return 0;
}
