/**
 * Expalin why declare an array as a pointer won't work
 * Used with mango.c, which provides the definition of array "mango"
 * from P96
 */
#include <stdio.h>

int main(void)
{
     extern char *mango; // must have this, otherwise "error: 'mango' undelcared"

     // Actually, as long as you re-declare
     // mango as a VARIABLE and a pointer, instead of an array,
     // you could get the value of of the first BYTE the orignial array
     //extern char *mango; // this works, as expected
     //extern int *mango;  // this works, as expected
     //extern float *mango;  // this works, as expected

     // Some experiment as below,
     // I guess it's "undefined behavior"
     //extern char mango; // this works, as expected
     //extern int mango; // this works, I don't know why
     //extern float mango;// this doesn't work, I could be sure why.

    // 1."mango" would be substituted by an address value, say <9890>,
    //
    // 2. Since new extern type "char *" overwrites the original
    // type "char [11]", the byte <9890> would be intepreted
    // as a pointer-to-char, which is a VARIABLE instead of an array.
    //
    // 3.Using "mango" alone as below would yield the value
    // of the variable instead of the address of the variable(as all varialbes),
    // which is 'h'('\0x68'). <-- this explanation has a problem, see below
    // == however, the value of the variable is deduced by the address and the
    // == type at the same time, so if "mango" is regardes as a pointer variable,
    // == 8 bytes from <9890> should be read, and the value of that 8 bytes
    // == won't be 'h'('\x68') anymore.
    // == So I guess it's just "undefined behavior", which leads to
    // == only the single byte at <9890> is read and passed to "%c".
    // == And that's why the following statement would print 'h' successfully.
    printf("mango[1] == %c\n", mango);

    // 4. And that's also why the follwing statement will cause "segmentation fault"
    // (because it says *(\x68+0), which is dereferencing a location not allocated to the program.)
    //printf("mango[1] == %c\n", mango[0]);

    return 0;
}
