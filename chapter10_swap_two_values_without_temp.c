#include <stdio.h>

int main(void)
{
    int a = 1, b = 2;
    printf("a == %d, b == %d\n", a, b);
    //swapping
    a = a - b;
    b = b + a;
    a = b - a;
    printf("a == %d, b == %d\n", a, b);
}