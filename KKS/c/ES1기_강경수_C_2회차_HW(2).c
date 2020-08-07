#include <stdio.h>

int main(void)
{
int score, score2;		
scanf("%d",&score); //0~100까지 숫자만 입력
score2 = score/10;
	
switch(score2)
	{
	case 10:
		printf("A\n");
		break;
	case 9:
		printf("A\n");
		break;
 	case 8:
		printf("B\n");
		break;
	case 7:
		printf("C\n");
		break;
	case 6:
		printf("D\n");
		break;	
	default:
		printf("E\n");
		break;	
	}
return 0;	
}
