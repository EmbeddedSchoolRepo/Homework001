/***********************************************************************************
복소수 class를 구현하자. 가독성이 좋고 철저하게 모듈화한 코드를 작성하자.
*************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define square(x) x*x
#define pi 3.141592
#define radian 180/pi


struct user_complex //C언어에서 복소수 class 구현
{
	double real; //실수
	double imagine; //허수 
	double hypo;  //극좌표 빗변
	double degree; //극좌표 각도 

	void (*set_val)(struct user_complex*,double,double); // <- 구조체 가독성및 모듈화를 위해 함수포인터 사용 

	struct user_complex (*sum)(struct user_complex*, struct user_complex*);
	struct user_complex (*sub)(struct user_complex*, struct user_complex*);
	struct user_complex (*multiple)(struct user_complex*, struct user_complex*);
	struct user_complex (*divide)(struct user_complex*, struct user_complex*);
	void (*init)(struct user_complex*); 
	void (*polar)(struct user_complex*); 
	void (*complexing)(struct user_complex*);
};

double Pythagorean(double a,double b); //피타고라스정리
void user_init(struct user_complex* self); //함수포인터 -> 함수 매칭 
void user_set_val(struct user_complex* self, double real, double imagine); //복소수 값 할당 
void user_polar(struct user_complex* self); //복소수 -> 극좌표 
void user_complexing(struct user_complex* self); //극좌표 -> 복소수 

struct user_complex user_sum(struct user_complex* self1, struct user_complex* self2);
struct user_complex user_sub(struct user_complex* self1, struct user_complex* self2);
struct user_complex user_multiple(struct user_complex* self1, struct user_complex* self2);
struct user_complex user_divide(struct user_complex* self1, struct user_complex* self2); 

int main(void)
{
	struct user_complex num1,num2;
	struct user_complex tmp1,tmp2,tmp3,tmp4; 

	user_init(&num1); 
	user_init(&num2);
	user_init(&tmp1); 
	user_init(&tmp2);
	user_init(&tmp3); 
	user_init(&tmp4);
	
	num1.set_val(&num1,3,5); //num1= 3+5j
	num2.set_val(&num2,5,10); //num2= 5+10j

	printf("이 class의 실수부는 %lf 입니다.\n",num1.real);
	printf("이 class의 허수부는 %lf 입니다.\n",num1.imagine);
	printf("이 class의 빗변은 %lf 입니다.\n",num1.hypo);
	printf("이 class의 각도는 %lf 입니다.\n",num1.degree*radian);

	tmp1 = tmp1.sum(&num1,&num2); // num1+num2 결과를 tmp구조체에 저장
	tmp2 = tmp2.sub(&num1,&num2); // num1-num2 결과를 tmp구조체에 저장
	tmp3 = tmp3.multiple(&num1,&num2);
	tmp4 = tmp4.divide(&num1,&num2);

	printf("%lf\n",tmp1.real);
	printf("%lf\n",tmp2.real);
	printf("%lf\n",tmp3.imagine);
	printf("%lf\n",tmp4.real);

	return 0;
}

void user_init(struct user_complex* self) // //함수포인터와 함수를 매칭해주는 함수 
{
	self->set_val = user_set_val;
	self->sum = user_sum;
	self->sub = user_sub;
	self->multiple = user_multiple;
	self->divide = user_multiple;
	self->init = user_init;
	self->polar = user_polar;
	self->complexing = user_complexing;
}


void user_set_val(struct user_complex* self, double real, double imagine) //실수부 허수부 값 지정
{
	self-> real = real;
	self-> imagine = imagine;
    self-> polar(self); //실수부 허수부 선언과 동시에 극좌표형식에 값 할당.
}

void user_polar(struct user_complex* self) //set_val이 선언되면 이 함수가 호출되어 set_val값 그대로 극좌표로 변환 
{
	self->hypo = Pythagorean(self->real,self->imagine);
	self->degree = atan(self->imagine/self->real); //radian 값임. 
}

void user_complexing(struct user_complex* self) //poloar -> complex 
{
	self->real = (self->hypo)*cos(self->degree);
	self->imagine = (self->hypo)*sin(self->degree);
}

struct user_complex user_sum(struct user_complex* self1,struct user_complex* self2)
{
	struct user_complex tmp; 

	tmp.real = self1->real + self2->real;
	tmp.imagine = self1->imagine + self2->imagine;
	
	return tmp; //복수의 값을 사용하기 위해 struct구조체 자체를 반환 할 수 있다.
}

struct user_complex user_sub(struct user_complex* self1, struct user_complex* self2)
{
	struct user_complex tmp;

	tmp.real =  self1->real - self2->real;
	tmp.imagine = self1->imagine - self2->imagine;

	return tmp;
}

struct user_complex user_multiple(struct user_complex* self1, struct user_complex* self2)
{
	struct user_complex tmp;
	
	tmp.hypo = self1->hypo * self2->hypo;
	tmp.degree = self1->degree + self2->degree;
	//tmp.complexing(&tmp);
	user_complexing(&tmp);

	return tmp;
}

struct user_complex user_divide(struct user_complex* self1, struct user_complex* self2)
{
	struct user_complex tmp;

	tmp.hypo = self1->hypo / self2->hypo;
	tmp.degree = self1->degree - self2->degree;
	//tmp.complexing(&tmp);
	user_complexing(&tmp);

	return tmp;
}

double Pythagorean(double a,double b) //피타고라스 정리 
{
	return  (sqrt(square(a) + square(b)));
}
