#include <stdio.h>
int main(void)
{
	int score;
	char rank;

	scanf("%d", &score);	

	while(score > 100 || score < 0)
	{
		printf("%d is not correct range\r\n", score);
		scanf("%d",&score);
	}
	
	if(score >= 90)
	{
		rank = 'A';
	}
	else if(score >= 80)
	{
		rank = 'B';	
	}
	else if(score >= 70)
	{
		rank = 'C';	
	}
	else if(score >= 60)
	{
		rank = 'D';	
	}
	else
	{
		rank = 'F';	
	}

	printf("%c\r\n", rank);

	return 0;
}
