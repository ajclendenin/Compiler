#include <stdio.h>

// generated from demo2.txt
int g(int x);

int main(void)
{
    int x = g(2);
    int y = g(0);
    int z = g(-3);

    printf("x=%d y=%d z=%d\n", x, y, z);
    return 0;
}
