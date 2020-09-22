/*
 * 정현파 교류전압이나 전류를 페이저로 변환하고 그 페이저를 복소수에서 배운
 * 극좌표 형식과 같은 것으로 취급하면 예상보다 훨씬 간단하게 정현파 교류회로에서의 
 * 복잡한 수식을 계산할 수 있음
 *  
 * 1. 복소수 표현은 극좌표계로 받는다(반지름, 각도) => 구조체로 표현하기
 * 2. 사칙연산에 해당하는 명령어와 함수를 맵핑(테이블 형태로)
 * 3. 연산자체가 복잡하지 않으니 과도하게 포인터 사용은 굳이 하지 않는다.
 * 4. 최종적으로 반지름과 각도로 표현되도록 함
*/

/***************************************************************************************************
*   Include	
***************************************************************************************************/
#include <stdio.h>
#include <math.h>

/***************************************************************************************************
*   Define	
***************************************************************************************************/
#define PI 3.1415926535

/***************************************************************************************************
*   Type Def	
***************************************************************************************************/
typedef struct polarPosition
{
    double radius;
    double degree;
} polarPosition; 

typedef struct orthogonalPosition 
{
    double real;
    double image;
} orthogonalPosition; 

typedef polarPosition (*CalcFuncPtr)(polarPosition, polarPosition);

typedef struct OperatingCmd
{
    char* cmd;
    CalcFuncPtr calc;
} OperatingCmd;

/***************************************************************************************************
*   Func Prototype	
***************************************************************************************************/
polarPosition Cal_add(polarPosition A, polarPosition B);
polarPosition Cal_sub(polarPosition A, polarPosition B);
polarPosition Cal_mux(polarPosition A, polarPosition B);
polarPosition Cal_div(polarPosition A, polarPosition B);
orthogonalPosition polarTorthogonal(polarPosition A);
polarPosition orthogonalTopolar(orthogonalPosition A);
polarPosition Calculator (polarPosition A, polarPosition B, char* opmode);

/***************************************************************************************************
*   Variable	
***************************************************************************************************/
OperatingCmd Op_Cmd[] = 
{
    {"ADD"   ,     Cal_add},
    {"SUB"   ,     Cal_sub},
    {"MUX"   ,     Cal_mux},
    {"DIV"   ,     Cal_div},
    {NULL    ,     NULL}
};

/***************************************************************************************************
*   Main	
***************************************************************************************************/
int main(void)
{
    polarPosition V1 = {10, -36.9}; //10-j36.9 
    polarPosition V2 = {10, 53.1};  //10-j53.1
    polarPosition Result1, Result2, Result3, Result4; 

    Result1 = Calculator(V1, V2, "ADD");
    Result2 = Calculator(V1, V2, "SUB"); 
    Result3 = Calculator(V1, V2, "MUX");
    Result4 = Calculator(V1, V2, "DIV");

    printf("ADD : radius = %.2f, degree = %.2f\n", Result1.radius, Result1.degree);
    printf("SUB : radius = %.2f, degree = %.2f\n", Result2.radius, Result2.degree);
    printf("MUX : radius = %.2f, degree = %.2f\n", Result3.radius, Result3.degree);
    printf("DIV : radius = %.2f, degree = %.2f\n", Result4.radius, Result4.degree);

    return 0;
}

/***************************************************************************************************
*   Func (Calc - add, sub, mux, div)
***************************************************************************************************/
polarPosition Calculator (polarPosition A, polarPosition B, char* opmode)
{
    OperatingCmd *cmdptr;

    for(cmdptr = Op_Cmd; cmdptr->cmd; cmdptr++)
    {
        if(*(cmdptr->cmd) == *opmode)
        {
            return cmdptr->calc(A, B);
        }
    }

    if(cmdptr->cmd == NULL)
    {
    }
}

polarPosition Cal_add(polarPosition A, polarPosition B)
{
    orthogonalPosition orTemp1;
    orthogonalPosition orTemp2;
    orthogonalPosition orTempResult;

    orTemp1 = polarTorthogonal(A);
    //printf("%f+j%f\n", orTemp1.real, orTemp1.image);

    orTemp2 = polarTorthogonal(B);
    //printf("%f+j%f\n", orTemp2.real, orTemp2.image);

    orTempResult.real = orTemp1.real + orTemp2.real;
    orTempResult.image = orTemp1.image + orTemp2.image;
    //printf("%f+j%f\n", orTempResult.real, orTempResult.image);

    return orthogonalTopolar(orTempResult);
}

polarPosition Cal_sub(polarPosition A, polarPosition B)
{
    orthogonalPosition orTemp1;
    orthogonalPosition orTemp2;
    orthogonalPosition orTempResult;

    orTemp1 = polarTorthogonal(A);
    orTemp2 = polarTorthogonal(B);

    orTempResult.real = orTemp1.real - orTemp2.real;
    orTempResult.image = orTemp1.image - orTemp2.image;
    //printf("%f+j%f\n", orTempResult.real, orTempResult.image);

    return orthogonalTopolar(orTempResult);
}

polarPosition Cal_mux(polarPosition A, polarPosition B)
{
    orthogonalPosition orTemp1;
    orthogonalPosition orTemp2;
    orthogonalPosition orTempResult;

    orTemp1 = polarTorthogonal(A);
    orTemp2 = polarTorthogonal(B);

    orTempResult.real = (orTemp1.real * orTemp2.real) - (orTemp1.image * orTemp2.image);
    orTempResult.image = (orTemp1.image * orTemp2.real) + (orTemp2.image * orTemp1.real);
    //printf("%f+j%f\n", orTempResult.real, orTempResult.image);

    return orthogonalTopolar(orTempResult);
}

polarPosition Cal_div(polarPosition A, polarPosition B)
{
    orthogonalPosition orTemp1;
    orthogonalPosition orTemp2;
    orthogonalPosition orTempResult;

    orTemp1 = polarTorthogonal(A);
    orTemp2 = polarTorthogonal(B);

    orTempResult.real = ((orTemp1.real * orTemp2.real) + (orTemp2.image * orTemp1.image)) /
                        (orTemp2.real * orTemp2.real + orTemp2.image * orTemp2.image);
    orTempResult.image = ((orTemp1.image * orTemp2.real) - (orTemp2.image * orTemp1.real)) /
                        (orTemp2.real * orTemp2.real + orTemp2.image * orTemp2.image);
    //printf("%f+j%f\n", orTempResult.real, orTempResult.image);

    return orthogonalTopolar(orTempResult);
}

/***************************************************************************************************
*   Driver	
***************************************************************************************************/
orthogonalPosition polarTorthogonal(polarPosition A)
{
    orthogonalPosition var;
    A.degree = PI * A.degree / 180;

    var.real = A.radius * cos(A.degree);
    var.image = A.radius * sin(A.degree);
    return var;
}

polarPosition orthogonalTopolar(orthogonalPosition A)
{
    /* 
     * 디그리 -> 라디안 : PI / 180 곱해줌
     * 라디안 -> 디그리 : 180 / PI 곱해줌   
     */
    polarPosition var;
    var.radius = sqrt(pow(A.real,2) + pow(A.image,2));
    var.degree = atan2(A.image, A.real) * 180/PI; //atan2가 -pi ~ pi 까지이기 때문에 음의 값 표현 가능
    return var;
}
