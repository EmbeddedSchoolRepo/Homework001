#include<stdio.h>
/*
void swap_str(char *str_a, char *str_b);


int main(void)
{
	char str_1[] = "angel";
	char str_2[] = "devil";
	
	printf("%s\n", &str_1[0]);
	printf("%p\n", &str_1[0]);
	printf("%s\n", &str_2[0]);
	printf("%p\n", &str_2[0]);

	swap_str(&str_1[0],&str_2[0]);

	printf("%s\n", &str_1[0]); 
	printf("%p\n", &str_1[0]);

	printf("%s\n", &str_2[0]);
	printf("%p\n", &str_2[0]);

	return 0;
}

void swap_str(char *str_a, char *str_b)
{
	char* temp;

	temp = str_a;
	str_a = str_b;
	str_b = temp;
	
	printf("%s\n", str_a);
	printf("%p\n", &str_a);

	printf("%s\n", str_b);
	printf("%p\n", &str_b);

}
*/ // 불가능하다!

void swap_str(char *str_a, char *str_b);

int main(void)
{
	char str_1[] = "angel";
	char str_2[] = "devil";

	printf("%s\n", str_1);
	printf("%s\n", str_2);

	swap_str(str_1,str_2);

	printf("%s\n", str_1);
	printf("%s\n", str_2);

	return 0;
}

void swap_str(char *str_a, char *str_b)
{
	int i= 0;
	char temp[6];

	for(i=0;i<6;i++)
	{
		temp[i] = *(str_a+i);  
	}

	for(i=0;i<6;i++)
	{
		*(str_a+i) = *(str_b+i);  
	}

	for(i=0;i<6;i++)
	{
		*(str_b+i) = temp[i];  
	}

}
