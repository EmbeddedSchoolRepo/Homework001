#include <stdio.h>

const int MAX = 3;

int main(void){
	int var[] = {10, 100, 200};
	int i, *ptr;

	ptr = var;

	for (i=0; i < MAX ; i++){

		printf("Address of var[%d] = %x\n", i, ptr);
		printf("value of car[%d] = %d\n", i ,*ptr);

		ptr++;
	}
	return 0;
}
