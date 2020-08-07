#include <stdio.h>

void SwapStr(char* StrTmp1, char* StrTmp2);

int main(void)
{
	char str1[] = "angle";
	char str2[] = "devil";

	printf("Before Change str1 : %s\n", str1);
	printf("Before Change str2 : %s\n", str2);

	SwapStr(str1, str2);

	printf("After Change str1 : %s\n", str1);
	printf("After Change str2 : %s\n", str2);

	return 0;
}

void SwapStr(char* StrTmp1, char* StrTmp2)
{
	char tmp;
	int i;

	for(i = 0; StrTmp1[i] != '\0'; i++)
	{
		tmp = StrTmp1[i];
		StrTmp1[i] = StrTmp2[i];
		StrTmp2[i] = tmp;
	}

}
