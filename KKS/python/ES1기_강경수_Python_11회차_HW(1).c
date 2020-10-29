#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct __OBJECT__
{
	int row; //행 
	int col; //열 
	int area; //면적 
	int status; //할당가능유무 
	int assign; //기 할당유무 
}Object;

int **n_by_n_space;
int num;
int num_row;
int num_col;
Object object[6];

void Object_init(Object* self,int row, int col)
{
	self->row = row;
	self->col = col;
	self->area = row*col;
	self->status = -1;
	self->assign = -1;
}

void Assign_Object(void)
{
	Object_init(object,2,2);
	Object_init(object+1,2,3);
	Object_init(object+2,3,3);
	Object_init(object+3,3,4);
	Object_init(object+4,5,2);
	Object_init(object+5,5,3);
}

void create_n_by_n_array(void)
{
	int i;

	srand(time(NULL));

	// 3 ~ 7
	num = rand() % 5 + 3;
	num = 10;
	num_row = 0;
	num_col = 0;

	n_by_n_space = (int **)malloc(sizeof(int *) * num);

	for (i = 0; i < num; i++)
	{
		n_by_n_space[i] = (int *)malloc(sizeof(int) * num);
	}
}

void sorting(void) //col or row의 크기가 num보다 작은지 확인. 
{
	int i;
	
	for(i=0;i<6;i++)
	{
		if((object[i].col>num-num_col)|(object[i].row>num-num_row)|(object[i].status==0))
		{
			printf("Too big\n");
			object[i].status = 0; //배열 불가능 
		}
		else if(object[i].assign == 1)
		{
			printf("Already\n");
		}
		else
		{
			object[i].status = 1; //배열 가능
			printf("area : %d num*num : %d \n",object[i].area,num*num);
		}
	}

}

int largest(void)
{
	int i;
	int largest;
	int max = 0;
	
	for(i=0;i<6;i++)
	{
		if((object[i].status==1)&&(object[i].area>max)&&(object[i].assign==-1))
		{
			max = object[i].area;
			largest = i;
			printf("object[i].area : %d\n",object[i].area);
		}
	}
	printf("object[largest].area : %d\n",object[largest].area);
	object[largest].assign = 1;
	return largest;
}

void fill_col(int largest)
{
	int i, j;

	for (i = 0; i < num; i++)
	{
		for (j = 0; j < num; j++)
		{
			if(i<=object[largest].row-1&&j<=object[largest].col-1)
			{
				n_by_n_space[i][j] = 1;
			}				
		}
	}
	num_col = num_col+object[largest].col;
}

void fill2(int largest)
{
	int i, j;

	for (i = 0; i < num; i++)
	{
		for (j = 0; j < num; j++)
		{
			if(i<=object[largest].row-1&&j<=object[largest].col-1)
			{
				n_by_n_space[i][j+num_col] = 2;
			}				
		}
	}
	num_col = num_col+object[largest].col;
}


void init_n_by_n_array(void)
{
	int i, j;

	for (i = 0; i < num; i++)
	{
		for (j = 0; j < num; j++)
		{
			n_by_n_space[i][j] = -1;
		}
	}
}

void print_n_by_n_array(void)
{
	int i, j;

	for (i = 0; i < num; i++)
	{
		for (j = 0; j < num; j++)
		{
			printf("%3d", n_by_n_space[i][j]);
		}

		printf("\n");
	}
}

void aa(void)
{
	for(i=0;i<num;i++)
	{
		num-num_col > 
	}
}

int main(void)
{
	create_n_by_n_array();
	init_n_by_n_array();
	Assign_Object();
	print_n_by_n_array();
	
	while(1)
	{
		sorting();
		fill(largest());
		print_n_by_n_array();
		
		for(i=0;i<num;i++)
		{
			num-num_col > object[i].col 
		}
	
	return 0;
}
