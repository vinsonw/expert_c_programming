/* subscript operator []
 * I just have to try this!
 */

int main(void)
{
    int a[10] = {1};
    6[a] = 7; // here it is!
    for (int i=0; i<10; i++)
        printf("%d==%d\n", i, a[i]);
}