#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

# define SWAP(x, y, temp) ( (temp)=(x), (x)=(y), (y)=(temp) )

int ran_num(int *arrp);
int average(int *arrp,int d_num);
int median(int *arrp, int m_num);
double dispersion(int *arrp,int *dis_arrp, int di_num, int average_num);
int partition(int list[], int left, int right);
void quick_sort(int list[], int left, int right);
/*
int variance(int *arrp);
int s_deviation*/

int main(void)
{
	int arr[200] = {0,};
	int dispersion_arr[200] = {0,};
	int i = 0;
	int num_cnt = 0; //100~200 랜덤값
	int average_val = 0; //평균값
	int medi_val = 0; //중간값
	int dispersion_val = 0;
	double st_deviation = 0;
	
	srand((unsigned int)time(NULL));  

	num_cnt=ran_num(&arr[0]);

	average_val = average(arr,num_cnt);
	medi_val=median(arr,num_cnt);
	dispersion_val = (int)dispersion(arr,dispersion_arr,num_cnt,average_val);
	st_deviation = sqrt(dispersion_val);
	
	
	for(i=0;i<num_cnt;i++)
	{
		printf("숫자%d : %d\n",i,arr[i]);
	}
	
	printf("평균값:%d\n",average_val);

	quick_sort(arr,0,num_cnt-1);

		for(i=0;i<num_cnt;i++)
	{
		printf("숫자%d : %d\n",i,arr[i]);
	}

	printf("중간값:%d\n",medi_val);

	printf("분산값:%d\n",dispersion_val);

	printf("표준편차:%lf\n",st_deviation);

    return 0;
}

int ran_num(int *arrp) 
{
    int num=0;
    int i=0;
    int j=0;

    j = rand()%101+100; // 100~200 난수 개수
	printf("%d\n",j);

    for(i=0;i<j;i++)
    {
        num  = rand()%101; //0~100 난수
        *(arrp+i) = num;
    }

	return j;
}

int average(int *arrp, int d_num)
{
	int i = 0;
	int num_sum = 0;
	int average_valf = 0;

	for(i=0;i<d_num;i++)
    {
        num_sum  += *(arrp+i);
    }
	average_valf = num_sum/d_num;
	return average_valf;
}
 
int median(int *arrp, int m_num)
{
	int temp1;
	int temp2;
	int temp3;

	if(m_num+1%2==0)//배열이 홀수인지 짝수인지 확인
	{
		temp1 = *(arrp+((m_num+1)/2));
		temp2 = *((arrp+((m_num+1)/2))-1);
		temp3 = (temp1+temp2)/2;
	}
	else
	{
		temp3 = *(arrp+(m_num+1)/2);
	}
	return temp3;			
}

double dispersion(int *arrp,int *dis_arrp, int di_num, int average_num)
{
	int i =0;
	int dis_num = 0;

		for(i=0;i<di_num;i++)
    {
        *(dis_arrp+i)  = (int)pow(*(arrp+i)-average_num,2);
		printf("분산값:%d\n",*(dis_arrp+i));
    }

		dis_num = average(dis_arrp,di_num);
		printf("dis_num:%d\n",dis_num);
		return dis_num;
}

int partition(int list[], int left, int right){
  int pivot, temp;
  int low, high;

  low = left;
  high = right + 1;
  pivot = list[left]; 

  do
  {
    do 
	{
      low++; 
    } 
	
	while (low<=right && list[low]<pivot);

    do 
	{
      high--;
    } 
	
	while (high>=left && list[high]>pivot);

    if(low<high)
	{
      SWAP(list[low], list[high], temp);
    }
  } 
  
  while (low<high);

  SWAP(list[left], list[high], temp);

  return high;
}

void quick_sort(int list[], int left, int right){

  if(left<right)
  {
    int q = 0;
	q = partition(list, left, right); //피봇위치 
    quick_sort(list, left, q-1);
    quick_sort(list, q+1, right); 
  }

}
