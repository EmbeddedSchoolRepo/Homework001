/*
 * 내가 있는 좌표(x, y) 및 7개의 주변 좌표를 랜덤하게 생성
 * 내가 있는 좌표로부터 각각의 좌표가 얼마나 멀리 떨어져 있는지 계측하기
 * 
 * 0. 좌표 표현을 어떤식으로 할까?
 * - 이차원 배열 과 구조체로 표현 하는 방법 2가지가 있음(우선 구조체로 표현해보자)
 * 
 * 1. 랜덤좌표 생성은 어떻게 할까?
 * - srand(), rand(), time() 함수 사용
 * 
 * 2. 좌표간 거리 구하는 계산은 함수로 모듈화
 * - squrt(), Pow() 함수 등을 사용 (math 라이브러리 추가) 
 * 
 * 3. 가장 가까운 거리에 있는 정보 획득은 어떤식으로 할까?
 * - 각각의 거리 length를 이미 구했기 때문에 length중 가장 짧은 곳의 index를 구해서
 *   해당 index에 해당하는 좌표 출력하기
 * - Position_miminumIndex를 완전 모듈화 하려면 Length 계산이 해당 함수 아래에 들어가게 구성하면 될듯
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define POS_CNT 7

typedef struct Pos
{
    int X;
    int Y;
} Pos;

void Position_Length(double * , const Pos * defaultPos, const Pos *pPos);
void Position_RandomMake(Pos *, int);
int Position_minimumIndex(const double *);

int main()
{
    Pos pos[POS_CNT];
    Pos myPos;  
    int i, index; 
    double length[POS_CNT];

    srand(time(NULL)); //Position_RandomeMake 함수 내에 들어가면 첫 출력이 아래 두문장이 동일한 값이 나옴?
    Position_RandomMake((Pos*)&myPos, 1);
    Position_RandomMake((Pos*)pos, POS_CNT);

    Position_Length((double*)length, (Pos*)&myPos, (Pos*)pos);
    
    index = Position_minimumIndex(length);
    printf("(%d , %d)\r\n",pos[index].X, pos[index].Y);
    return 0;
}

void Position_RandomMake(Pos * pPos, const int count)
{
    int i;

    for(i = 0; i < count; i++)
    {
//      pPos[i].X = rand();
//      pPos[i].Y = rand();
        (pPos+i)->X = rand()%10;
        (pPos+i)->Y = rand()%10;
    }
}

void Position_Length(double *pLength, const Pos * defaultPos, const Pos * pPos)
{
    int i;

    for(i = 0; i < POS_CNT; i++)
    {
        pLength[i] = (double) sqrt(pow(pPos[i].X - defaultPos->X, 2) + pow(pPos[i].Y - defaultPos->Y, 2));
        printf("%5.2f\r\n", pLength[i]);
    }
}

int Position_minimumIndex(const double *pLength)
{
    int i;
    int index = 0;
    double min = pLength[index]; 

    for(i = 1; i < POS_CNT; i++)
    {
        if(pLength[i] < min)
        {
           min = pLength[i];
           index = i; 
        }
    }

    return index;
}
