#include <stdio.h>

int main(void)
{
	int var;
	int *ptr;
	int **pptr;

	var = 3000;

	ptr = &var;

	pptr = &ptr;

	printf("Value of each variables\n");
	printf("Value of var = %d\n", var);
	printf("Value available at *ptr = %d\n", *ptr);
	printf("Value available at **pptr = %d\n", **pptr); 

	printf("\nAddress of each variables\n");
	printf("Address of var = %x\n", &var);
	printf("Value of *ptr = %x\n", ptr);
	printf("Address of *ptr = %x\n", &ptr);
	printf("Value of **pptr = %x\n", pptr); 

	return 0;
}
