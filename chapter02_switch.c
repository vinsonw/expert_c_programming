#include <stdio.h>

int main(void)
{
    int i=4;
    const int two=4;
    switch (i)
    {
        case 1:
            printf("1\n");
            break;

        // Here lies a bug:
        //     error: case label does not reduce to an integer constant
        //    12 |     case two:
        //       |     ^~~~ 
        case two:
            printf("here is two.\n");
            break;
        case 2:
            printf("2\n");
            break;
        case 3:
            printf("3\n");
            break;
        
        default:
            printf("default!\n");
            break;
    }
}