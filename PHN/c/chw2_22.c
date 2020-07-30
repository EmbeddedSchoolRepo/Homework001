#include <stdio.h>

int main(void)
{
	int score;
	char grade;

	printf("what score do you have? ");
	scanf("%d", &score);

	switch(score/10)
	{
		case 10:
		case 9:
			grade = 'A';
			break;
		case 8:
			grade = 'B';
			break;
		case 7:
			grade = 'C';
			break;
		case 6:
			grade = 'D';
			break;
		default:
			grade = 'F';
			break;
		
	}
	printf("점수는 %d점이고, 등급은 %c입니다.\n",score, grade);
	return 0;

}
