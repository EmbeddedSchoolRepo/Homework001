#include <stdio.h>

int main(void)
{
    int i,j;
    int a[2][3] = {{0,1,2},{3,4,5}};
    
    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 3; j++)
        {
           printf("%p\r\n", &a[i][j]); 
        }
    }
    printf("\n");
    printf("%p\r\n", &a);
    printf("%p\r\n", &a+1);
    printf("%p\r\n", a+1);
    printf("%p\r\n", *a);
    printf("%p\r\n", *a+1);
    printf("%d\r\n", **a);

    return 0;
}
