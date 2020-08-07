#include <stdio.h>
#include <time.h>
int* getRandom(void){
	static int r[10];
	int i;

	srand((unsigned)time(NULL));

	for(i = 0; i<10; ++i){
		r[i] = rand();
		printf("%d\n", r[i]);
	}
	return r;
}
int main(void){
	int *p;
	int i;
	p = getRandom();
	
	for (i=0; i<10; i++){
		printf("*(p+[%d]) : %d\n", i, *(p+i));
	}
	return 0;
}
