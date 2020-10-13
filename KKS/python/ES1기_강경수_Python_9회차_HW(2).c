/*animal.h*/

#ifndef ANIMAL_H
#define ANIMAL_H

typedef struct __ANIMAL__ Animal;
typedef struct __BEAR__ Bear;

/*부모*/
struct __ANIMAL__
{
	void (*whattype)(Animal*); // type이 무엇인지계산
	void (*howold)(Animal*); //몇살인지 계산
	
	int age; //태어난 년도  
	int type; // 파충류 : 1, 포유류 : 2, 조류 : 3, 
};

Animal* animal_init(void);
void animal_howold(Animal* self);
void animal_whattype(Animal* self);

/*자식*/
struct __BEAR__
{
      //부모구조체//
	  Animal parent;
	  //자식의 새로운 메서드 
	  void  (*isliving)(Bear*); 
	  //자식의 새로운 변수
	  int status; // 0: dead 1: living 
};

Bear* bear_init(void);
void bear_isliving(Bear* self);

#endif

/*animal.c*/
/*#include <animal.h>*/
#include <stdlib.h>
#include <stdio.h>

Animal* animal_init(void)
{
	Animal* animal = malloc(sizeof(Animal));
	
	printf("birth day: EX) 1995\n");
	scanf("%d",&(animal->age));
	printf("1: laptile 2: mam 3: bird\n");
	scanf("%d",&(animal->type)); 
	
	animal->howold = animal_howold;
	animal->whattype  = animal_whattype;
	
	return animal;
}

void animal_howold(Animal* self)
{
	int age = 2020 - (self->age);
	printf("its  %d years old\n",age);
}

void animal_whattype(Animal* self)
{
	switch(self->type)
	{
		case(1) : printf("is laptile\n");
				  break;
		case(2) : printf("is mam\n");
				  break;
		case(3) : printf("is bird\n");
				  break;
		default : break;
	}
}

Bear* bear_init(void)
{
	Bear* bear = malloc(sizeof(Bear));
	
	/*animal 의 주소와 bear->animal의 주소가 같기때문에 이렇게 사용 가능*/
	/*__BEAR__ 맨 처음 struct인자가 parent여야 하는 이유*/
	
	Animal* animal = (Animal*)bear;
	
	/*연산자 오버라이딩을 사용할 경우 수정하여 자식임의로 수정*/
	animal->howold =  animal_howold;
	animal->whattype = animal_whattype;
	
	printf("birth year : EX) 1995\n");
	scanf("%d",&(animal->age));
	printf("1: laptile 2: mam 3: bird\n");
	scanf("%d",&(animal->type)); 
	
	bear->isliving = bear_isliving;
	scanf("%d",&(bear->status));
}

void bear_isliving(Bear* self)
{
	switch(self->status)
	{
		case(0) : printf("bear sis dead");
				  break;
		case(1) : printf("bear is alive");
				  break;
		default : break;
	}
}
	
int main(void)
{
	Animal* animal = animal_init();
	Bear* bear = bear_init();

	return 0;
}