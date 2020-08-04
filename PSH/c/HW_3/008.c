#include <stdio.h>

int main(void)
{
	int var = 20; 
	int *ip;

	ip = &var;

	printf("Address of var vairable :%x\n", &var);
	printf("Address of var vairable :%x\n", ip);
	printf("Address of var vairable :%d\n", *ip);

	return 0;
}


