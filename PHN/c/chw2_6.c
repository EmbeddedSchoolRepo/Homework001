#include <stdio.h>

int main(void)
{
	int val1, val2;
	int cal1, cal2, cal3;
	int res1, res2, res3, res4;

	printf("첫번째 세자리 숫자를 입력하시오: ");
	scanf("%d", &val1);
	printf("두번째 세자리 숫자를 입력하시오: ");
	scanf("%d", &val2);

	res1 = val2%10;
	res2 = (val2%100-res1)/10 ;
	res3 = val2/100;

	printf("val1와 val2의 일의자리 곱: %d\n",val1*res1);
	printf("val1와 val2의 십의자리 곱: %d\n",val1*res2);
	printf("val1와 val2의 백의자리 곱: %d\n",val1*res3);
	printf("val1 * val2 = %d\n",val1*val2);

	return 0;	
	
}

