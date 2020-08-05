
#include <stdio.h>

// 명제. x^3 을 미분하면 → 3x^2 
// 즉, x =5일때의 미분값→ 75 이다.
// 사용이 용이하게 함수로 구현 
// f(a)로 수렴하는 f(a+h)가 존재
// 이때 h는 a+로 수렴
// 즉 h는 작으면 작을수록 좋다.
// 그러므로 h는 double형으로 선언

int integral(double a,double *result_valuef) //포인터 변수사용이유 → 변수조작이 용이함.
{
	double h =0.0001; //f(a+h) 의 h
	double function_valuea = 0;//a값만 넣었을때 함수값
	double function_valueh = 0;//(a+h)값을 넣었을때 함수값
	*result_valuef = 0; //함수에서의 미분결과값
    
	function_valuea = ((a)*(a)*(a));//pointer가 가르키는 값 세제곱
	function_valueh = ((a+h)*(a+h)*(a+h));

	*result_valuef = (function_valueh-function_valuea)/((a+h)-a);
	
	return 0;
	
}

int main(void)
{
	double input = 0; //결과값
	double result_valuem = 0;//main에서의 미분값

	printf("x값을 입력하세요:");
	scanf("%lf",&input);
	printf("\n");
	integral(input,&result_valuem);
	printf("미분결과:%lf\n",result_valuem); 
	
}
