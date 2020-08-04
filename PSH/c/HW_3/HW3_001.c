#include <stdio.h>

void String_Swap(char* strA, char* strB)
{
	char *temp;

	temp = strA;
	strA = strB;
	strB = temp;
}

int main(void)
{
	char str1[] = "angel";
	char str2[] = "devil";

	printf("0x%x\n", str1);
	printf("0x%x\n", str2);
	printf("%s\n", str1);
	printf("%s\n", str2);

	String_Swap(str1, str2);

	printf("0x%x\n", str1);
	printf("0x%x\n", str2);
	printf("%s\n", str1);
	printf("%s\n", str2);

	return 0;
}


