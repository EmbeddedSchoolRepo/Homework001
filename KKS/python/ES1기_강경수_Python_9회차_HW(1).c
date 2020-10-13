/* rect.h */
#ifndef RECT_H
#define RECT_H

typedef struct __RECT__ Rect;

struct __RECT__ 
{
	double x;
	double y;
	double width;
	double height;

	void (*move)(Rect*,double,double,double,double);
	void (*status)(Rect*);
};

void rect_move(Rect* self, double x,double y, double width, double height);
void rect_status(Rect* self);
Rect* rect_init(void);

#endif

/*rect.c*/
/*#include <rect.h>*/
#include <stdlib.h>
#include <stdio.h>

void rect_move(Rect* self, double x,double y, double width, double height)
{
	printf("rect_move");
	self->x = x;
	self->y = y;
	self->width = width;
	self->height = height;
}

void rect_status(Rect* self)
{
	printf("rect_status");
	printf("x : %lf y : %lf \n width : %lf height : %lf",	
			self->x,self->y,self->width,self->height);	
}

Rect* rect_init(void)
{
	Rect* rect = malloc(sizeof(Rect));
	
	rect->move = rect_move;
	rect->status = rect_status;
	
	return rect;
}

/*main.c*/
int main(void)
{
	Rect* rect = rect_init();
	rect->move(rect,10,20,30,40);
	rect->status(rect);
}
	
	

