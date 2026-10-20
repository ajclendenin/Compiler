#include <stdio.h>

int f(int a, int b, int c);

int main()
{
    int x = f(1, 2, 3);
    int y = f(-4, 1, 5);
    int z = f(x, y, 2);

    printf("x=%d y=%d z=%d\n", x, y, z);
    return 0;
}
