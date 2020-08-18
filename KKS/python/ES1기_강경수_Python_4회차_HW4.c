/* 다음달 승진을 압두고 있는 경찰관이 있다.

    관할구에 범죄가 발생하지 않아야 승진을 할 수 있다.

    통계 조사 결과 해당구의 한 해 범죄 회수가 10 건이라고 한다.

    다음달에 범죄가 발생하지 않을 확률을 구하고 이 자료에 입각하여 경찰관은 무엇을 준비해야할지를 논하고 구현하시오.

    (힌트: 푸아송 분포)*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(void)
{
	double lambda = 0;
	double m_lambda = 0;
	double Poisson = 0;

	lambda = (double) 10/12; //1개월 동안 발생할 사건수 
	
	Poisson =(exp((-1)*lambda)*pow(lambda,0))/1;
	printf("%f\n",Poisson); //사건이 발생하지 않을 확률

	return 0;
}
