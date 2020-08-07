#include <stdio.h>
#define N 10

void swap(char str1[], char str2[]){
	char swap_str ;
	int i;
	
	for( i = 0 ; i < N ; i++ ){		
		swap_str = str1[i];
		str1[i] = str2[i];
		str2[i] = swap_str;
	}
	

}

void main(void)
{
	char str1[N] = "angel";
	char str2[N] = "devel";
	
	printf("[before swap] str1: %s, str2: %s\n", str1, str2);
	swap(str1, str2);
	printf("[After swap]  str1: %s, str2: %s\n", str1, str2);
}
	
	

