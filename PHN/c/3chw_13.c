#include <stdio.h>



double getAverage(int arr[], int size){

	int i;
	double avg = 0;
	double sum = 0;

	for ( i = 0 ; i < size ; ++i ){
		sum += arr[i];
	}

	avg = sum / size;

	return avg;
}

int main(){
	int balance[5] = {1000, 2, 3, 17, 50};
	double avg = 0;

	avg = getAverage( balance, 5 );

	printf("Average value is: %f ", avg);

	return 0;
	
}
