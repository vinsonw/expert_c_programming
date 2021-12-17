#include <stdio.h>

int main(void)
{
    const int i = 1;
    int *pi = &i;
    printf("now i==%d\n", i);
    *pi = 2;
    printf("now i==%d\n", i);
}
