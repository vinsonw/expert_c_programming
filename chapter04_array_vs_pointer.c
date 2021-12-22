/**
 * Expalin why declare an array as a pointer won't work
 * Used with mango.c, which provides the definition of array "mango"
 * from P96
 */
#include <stdio.h>

int main(void)
{
    /*
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * PART I *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
    */

    extern char *mango; // must have this, otherwise "error: 'mango' undelcared"
    // printf("mango[1] == %c\n", mango[0]);

    // the above statement will cause "segmentation fault"
    // Because when "mango" is re-declared as a pointer, which is a variable,
    // [indirect memory reference] is used, as opposed to array, which uses [direct memory reference].  
    // Say "mango" corresponds to <9890> in symbol table,
    // now when use "mango[0]", i.e. *(mango+0), the value of <9890> (as a pointer, which is a
    // 8-byte unsigned long on this machine) would be read, say the value is X, then the value would 
    // be added 0*1(leng of char in byte), the result is still X, then the 
    // byte (it would be read as a char, that is to say only one byte would be read, because the pointer type is pointer-to-char)
    // at address X would be read as the value of expression "*(mango+0)". 
    // BUT the byte at address X has not been allocated for us to access, thus the segmentation fualt. 

    // Now we know re-delcaring array as pointer is the first sin, then under the first sin, dereferenceing 
    // the pointer is the second sin.

    // Here is how to mitigate the sins:

    char * pc = (char *)&mango; // cast "&mango"(char **) to char*
    // becuase "pc" is a real pointer(which has it's seperate storage),
    // it could use indirection reference, that is to say it could do the jump thing as intended.
    for (; *pc!=0; pc++)
        printf("%c", *pc); // outcome: helloworld


    /* 
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * PART II * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
    */

    // Here is some interesting experiment, especially the float one:

     // Actually, as long as you re-declare
     // mango as a general integral type, including pointer(which is an 8-byte 
     // unsigned long int on this machine), char, int, etc. instead of an array,
     // you could get the value of of the lowest BYTE(because of little-endian) of the integral type you declared when
     // you cast the integral type to a char using "%c" in printf(), which is 'h', which is the first byte of the original array

     // Some experiment as below:
     //extern char *mango; // this works, as expected
     //extern int *mango;  // this works, as expected
     //extern float *mango;  // this works, as expected

     //extern char mango; // this works, as expected
     //extern int mango; // this works, I don't know why <- Now I know.

     // But when you re-declare mango as a float, you couldn't simply read the lowest byte 
     // when you cast the float to char using "%c" in printf(), instead 4 bytes above <9890>
     // would be read and interpreted as a float number according to IEEE-754, then this number
     // would be cast to char, which is a nonsense symbol since there's no character corresponds to this
     // huge number.
    //  extern float mango;// this doesn't work, I couldn't be sure why. <- Now I know.

    // mango as float bit pattern:
    // 1. float is 4-byte long on this machine, therefore only "hell" that occupies 4 bytes in "helloworld" 
    // will be read as the float 
    // 2. 'h','e','l','l' occupy 4 bytes, which are stored from lower address to
    // to higher address. Namely, 'h' occupies <9890>, 'e' occupies <9891>,
    // 'l' occupies <9892>, 'l'(the 2nd one) occupies <9893>
    // 3. when these 4 bytes are interpreted as a float, on this x86 little-endian machine,
    // byte <9893> is the most significant byte, byte <9890> is the least significant, the bit 
    // pattern of the float should be in the order of <9893><9892><9891><9890>, which corresponds
    // to the bit pattern of 'l','l','e','h' respectively. Therefore, the bit pattern fo the float
    // is '01101100011011000110010101101000' (from python ''.join(format(ord(c),'08b') for c in 'lleh'))
    // 4. According to IEEE-754, 01101100011011000110010101101000 is 1143141483620823940762435584F
    // (converter: https://www.h-schmidt.net/FloatConverter/IEEE754.html)
    // printf("mango[1] == %f\n", mango); // outcome: mango[1] == 1143141483620823940762435584.000000
    // printf("mango[1] == %c\n", mango); // outcome: a nonsense symbol


    return 0;
}
