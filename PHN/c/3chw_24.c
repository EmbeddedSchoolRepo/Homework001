#include <stdio.h>
#define N 5

void main(void){
	int i, j, k ;
        int uporder;
	int bal[N] = {1000, 2, 3, 17, 50};

	for(i = 0 ; i < N ; i++){
		for(j = 0 ; j < N - i ; j++){
			if (bal[i] > bal[i+1]){
				uporder = bal[i];
				bal[i] = bal[i+1];
				bal[i+1] = uporder;		
			}
		}
     	}
	for(k=0 ; k < N ; k++)
        {
                printf("%d ", bal[k]);
        }

}
