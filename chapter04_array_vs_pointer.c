/**
 * Expalin why declare an array as a pointer won't work
 * Used with mango.c, which provides the definition of array "mango"
 * from P96
 */
#include <stdio.h>

int main(void)
{
     extern char *mango; // must have this, otherwise "error: 'mango' undelcared"
     int orange[100] = {[1]=101};


    // 1."mango" would be substituted by an address value, say <9890>,
    //
    // 2. Since new extern type "char *" overwrites the original
    // type "char [11]", the byte <9890> would be intepreted
    // as a pointer-to-char, which is a VARIABLE instead of an array.
    //
    // 3.Using "mango" alone as below would yield the value
    // of the variable instead of the address of the variable(as all varialbes),
    // which is 'h'('\0x68'). And that's why the following statement would print 'h' successfully.
    printf("mango[1] == %c\n", mango);
    // 4. And that's also why the follwing statement will cause "segmentation fault"
    // (because it says *(\x68+0), which is dereferencing a location not allocated to the program.)
    printf("mango[1] == %c\n", mango[0]);
    printf("orange[1] == %d\n", orange[1]);

    return 0;
}
