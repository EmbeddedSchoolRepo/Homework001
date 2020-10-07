/***********************************************************************************

 

C에서 복소수 class를 구현하자. 가독성이 좋고 모듈화한 코드를 작성하자.

 

*************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define square(x) x*x
#define pi 3.141592f
#define radian 180/pi

 

typedef struct _complex
{
	double real; 
	double imagine;
}complex;

 

typedef struct _phasor
{
	double hypo;
	double degree;
}phasor;

void phasor2complex(phasor z_p, complex* z_c);
void complex2phasor(phasor* z_p, complex z_c);
complex *complex_sum(complex z1, complex z2);
complex *complex_sub(complex z1, complex z2);
complex *complex_mul(complex z1, complex z2);
complex *complex_div(complex z1, complex z2);
void conjugate(complex *z);
double pythagorean(double a,double b);

int main(void)
{
	complex num1 = {.real = 5,.imagine = 3};
	complex num2 = {.real = 3,.imagine = -3};

	phasor num3 = {15,30};
	phasor num4 = {9,60};

	complex *c_tmp;
	phasor  *p_tmp;

	complex2phasor(p_tmp,num1);
	printf("hypo : %.4f, degree : %.4f\n", p_tmp->hypo, p_tmp->degree);	

	phasor2complex(num3,c_tmp);
	printf("real : %.4f, imagine : %.4f\n", c_tmp->real, c_tmp->imagine);
	
	return 0;
}

void phasor2complex(phasor z_p, complex* z_c) //phasor -> complex 
{
	z_c->real = z_p.hypo*cos(z_p.degree);
	z_c->imagine = z_p.hypo*sin(z_p.degree);
}

void complex2phasor(phasor* z_p, complex z_c) //complex -> phasor
{
     z_p->hypo = pythagorean(z_c.real,z_c.imagine);
     z_p->degree = atan(z_c.imagine/z_c.real); //radian 
}

complex *complex_sum(complex z1, complex z2)
{
    complex *result = (complex*)malloc(sizeof(complex));
    result->real = z1.real + z2.real;
    result->imagine = z1.imagine + z2.imagine;
  
    return result;
}

 

complex *complex_sub(complex z1, complex z2)
{
    complex *result = (complex*)malloc(sizeof(complex));
    result->real = z1.real - z2.real;
    result->imagine = z1.imagine - z2.imagine;

    return result;
}

 

complex *complex_mul(complex z1, complex z2)
{
    phasor z_tmp1;
    phasor z_tmp2;
    phasor z_result;

    complex *z_return = (complex*)malloc(sizeof(complex));
    complex2phasor(&z_tmp1,z1);
    complex2phasor(&z_tmp2,z2);

    z_result.hypo = z_tmp1.hypo * z_tmp2.hypo;
    z_result.degree = z_tmp1.degree * z_tmp2.degree;
    phasor2complex(z_result,z_return);

    return z_return;
}

 

complex *complex_div(complex z1, complex z2)
{
    phasor z_tmp1;
    phasor z_tmp2;
    phasor z_result;

    complex *z_return = (complex*)malloc(sizeof(complex));
    complex2phasor(&z_tmp1,z1);
    complex2phasor(&z_tmp2,z2);

    z_result.hypo = z_tmp1.hypo / z_tmp2.hypo;
    z_result.degree = z_tmp1.degree - z_tmp2.degree;

    phasor2complex(z_result,z_return);

    return z_return;
}

 

void conjugate(complex *z)
{
    z->imagine *= -1;
}

double pythagorean(double a,double b) //피타고라스 정리 
{
	return (sqrt(square(a) + square(b)));
}
