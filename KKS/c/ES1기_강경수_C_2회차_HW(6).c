#include <stdio.h>
 
int main(void)
{
    //변수선언//
	int a, b; //곱할값
	int c;    //n의자리 정수 추출 
	unsigned int pd_value; //곱셈결과
	unsigned int arr[4];
	int cnt=0;
	int arr_sumcnt=0;
	
	//값입력//
	scanf("%d %d",&a, &b);
	
	//자릿수추출및 저장//
	while(b>0)
	{
		c = (b%10);
		pd_value = a*c;
		b = b/10;
		arr[cnt] = pd_value;
		cnt++;
	}
	//출력//
	printf("(3)--%d\n",arr[0]);
	printf("(4)--%d\n",arr[1]);
	printf("(5)--%d\n",arr[2]);
	arr[3] =arr[0]+arr[1]*10+arr[2]*100;
	printf("(6)--%d\n",arr[3]);
 
	return 0;
}
