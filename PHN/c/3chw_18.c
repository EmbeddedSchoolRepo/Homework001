#include <stdio.h>

int main(void){
	int var;
	int *ptr;
	int **pptr;

	var = 3000;

	ptr = &var;

	pptr = &ptr;

	printf("value of var = %d\n", var);
	printf("value available at *ptr = %d\n", *ptr);
	printf("vlaue available at *pptr = %d\n", **pptr);

	return 0;
}

