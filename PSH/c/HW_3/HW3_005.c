#include <stdio.h>

int main(void)
{
    double d = 3.14;
    char c = 'a';
    int n = 7;
    char b = 'c';


    printf("%p\r\n", &d);
    printf("%p\r\n", &c);
    printf("%p\r\n", &n);
    printf("%p\r\n", &b);

    printf("%ld", sizeof(double));
    printf("%ld", sizeof(char));
    printf("%ld", sizeof(int));
    printf("%ld", sizeof(char));

    return 0;
}
