#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _LOCATION{
	int x;
	int y;
	int distance;
}location;

void random_xy(location *ploc, int x, int y); //구조체에 랜덤값 대입하는 함수. 
int user_distance(location *ploc,location *ploc_def); //받는 인자는 원점에 관한 x,y데이터
int user_random(void);
double user_sqrt(int num);

int main(void){

	int i=0;
	int MIN=1000;

	srand(time(NULL));
	location loc[8]; //값을 저장할 구조체 배열
	random_xy(&loc[0],user_random(),user_random()); //기준좌표
	for(i=1;i<8;i++){
		random_xy(&loc[i],user_random(),user_random()); //랜덤좌표 
	}

	printf("기준X좌표:%d" "기준Y좌표:%d\n",loc[0].x,loc[0].y);

	for(i=1;i<8;i++){
		printf("랜덤X좌표:%d" "랜덤Y좌표:%d\n",loc[i].x,loc[i].y);
	}

	for(i=1;i<8;i++){
		printf("거리%d:%d\n",i,user_distance(&loc[i],&loc[0]));
	}

	for(i=1;i<8;i++){
		if(loc[i].distance<MIN){
			MIN = loc[i].distance;
		}
	}
	
	printf("최소거리%d\n",MIN);

	return 0;
}

void random_xy(location *ploc, int x, int y){
	ploc->x=x;
	ploc->y=y;
}

int user_distance(location *ploc, location *ploc_def){  //받는 인자는 원점에 관한 x,y데이터
	double dis;
	int x1,x2,y1,y2;
	x1 = ploc->x;
	x2 = ploc_def->x;
	y1 = ploc->y;
	y2 = ploc_def->y;

	dis = user_sqrt((abs(x1-x2))*(abs(x1-x2)) + (abs(y1-y2))*(abs(y1-y2)));
	ploc->distance = dis;
	return (int)dis;
}

int user_random(void){
	return rand()%100+1;
}

double user_sqrt(int num){
	double key = num;
	int i = 0;
	for(i=0;i<10;i++)
	{
		key=key-(((key*key)-num)/(2*num));
	}
	return key;
} //Newton's method

