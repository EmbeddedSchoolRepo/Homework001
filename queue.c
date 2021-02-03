/*
 * queue.c
 *
 * Created: 2021-02-02 오전 10:28:39
 *  Author: KKS
 */ 

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct _circleQueue
{
	uint8_t data[MAX_Q_SIZE];
	uint8_t rear,front;
}Queue;


void init_queue(Queue *q)
{
	//q->data = (uint8_t*)malloc(sizeof(uint8_t)*MAX_Q_SIZE);
	q->rear = 0;
	q->front = 0;
}

uint8_t isEmpty(Queue *q)
{
	if((q->front==q->rear))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

uint8_t isFull(Queue *q)
{
	if(((q->rear+1) % MAX_Q_SIZE) == q->front)
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

void enque(Queue *q, uint8_t rx_data)
{
	if(isFull(q))
	{
		printf("Q_FULL!\n");
		return;
	}
	q->rear = (q->rear+1) % MAX_Q_SIZE; 
	q->data[q->rear] = rx_data;
	return;
}

uint8_t deque(Queue *q)
{
	if(isEmpty(q))
	{
		printf("Q_EMTPY!\n");
		return ERROR;
	}
	else
	{
		q->front = (q->front + 1) % MAX_Q_SIZE; 
		return q->data[q->front];
	}
}