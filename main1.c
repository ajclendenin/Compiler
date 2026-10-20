#include <stdio.h>

int f(int a, int b, int c);
int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int quot(int a, int b);
int rsub(int b, int a);
int answer(void);
int sum(void);
int scale(int x);
int tight(int a, int b);
int spaced(int a, int b);

int main()
{
    int x = f(1, 2, 3);
    int y = f(-4, 1, 5);
    int z = f(x, y, 2);

    printf("x=%d y=%d z=%d\n", x, y, z);

    printf("add(2, 3)     = %d (expect 5)\n", add(2, 3));
    printf("add(-2, -3)   = %d (expect -5)\n", add(-2, -3));
    printf("sub(10, 3)    = %d (expect 7)\n", sub(10, 3));
    printf("sub(3, 10)    = %d (expect -7)\n", sub(3, 10));
    printf("mul(-4, 6)    = %d (expect -24)\n", mul(-4, 6));
    printf("quot(17, 5)   = %d (expect 3)\n", quot(17, 5));
    printf("quot(-17, 5)  = %d (expect -3)\n", quot(-17, 5));
    printf("rsub(10, 3)   = %d (expect 7)\n", rsub(10, 3));
    printf("answer()      = %d (expect 42)\n", answer());
    printf("sum()         = %d (expect 7)\n", sum());
    printf("scale(5)      = %d (expect 501)\n", scale(5));
    printf("tight(4, 5)   = %d (expect 20)\n", tight(4, 5));
    printf("spaced(1, 1)  = %d (expect 2)\n", spaced(1, 1));
    return 0;
}
