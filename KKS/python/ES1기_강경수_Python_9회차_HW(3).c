#include <stdio.h>
#include <stdlib.h>

/*int형을 char형으로 typecsting하여서 byte로 쪼갤 수 있는지 확인해보자. */
/*pointer 주소도 쪼갤 수 있는지 확인하자.*/ 

int main(void)
{
	int num = 0x12345678; //8BYTE, LITTLE ENDIAN
	int *num_p = &num;
	printf("hex val : %x\n",(char)num);	
	printf("pointer val1 : %p\n",(char*)num_p);	  //000000000065FE14
	printf("pointer val2 : %p\n",(char*)num_p+1); //000000000065FE15 

}


