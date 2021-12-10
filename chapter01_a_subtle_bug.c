#include <stdio.h>

int array[] = {23, 34, 12, 17, 204, 99, 16};
#define TOTAL_ELEMENTS (sizeof(array) / sizeof(array[0]))

int main(void)
{
    int d = -1, x;
    int flag=0;

    // Here lies a bug:
    // "The defined variable TOTAL_ELEMENTS has type unsigned long"
    // "So variable d is promoted to unsigned long, interpreting -1 as an unsigned int yields"
    // "a big positive number, making the clause(expression) false"
    if (d <= TOTAL_ELEMENTS -2)
        flag=1;
    printf("flag==%d\n", flag); // flag is still 0

    // To remedy the bug:
    // do typecast immediately on TOTAL_ELEMENTS
    if (d <= (int)TOTAL_ELEMENTS -2)
        flag=1;

    printf("flag==%d\n", flag); // flag has been assigned value 1
}