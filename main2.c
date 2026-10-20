#include <stdio.h>

int g(int x);
int square(int x);
int cube(int x);
int eight(int a, int b, int c, int d, int e, int f, int g, int h);
int nested(int a, int b, int c, int d);
int poly(int x);
int deep(void);
int avg(int a, int b, int c);
int reorder(int c, int a, int b);
int long_name_1(int first_value, int second_value);
int CamelCase(int Width, int Height);

int main()
{
    int x = g(2);
    int y = g(0);
    int z = g(-3);

    printf("x=%d y=%d z=%d\n", x, y, z);

    printf("square(-7)               = %d (expect 49)\n", square(-7));
    printf("cube(-3)                 = %d (expect -27)\n", cube(-3));
    printf("eight(1, ..., 8)         = %d (expect 36)\n", eight(1, 2, 3, 4, 5, 6, 7, 8));
    printf("nested(10, 4, 3, 1)      = %d (expect 8)\n", nested(10, 4, 3, 1));
    printf("poly(3)                  = %d (expect 23)\n", poly(3));
    printf("poly(-2)                 = %d (expect -27)\n", poly(-2));
    printf("deep()                   = %d (expect 55)\n", deep());
    printf("avg(4, 5, 9)             = %d (expect 6)\n", avg(4, 5, 9));
    printf("reorder(2, 10, 3)        = %d (expect 14)\n", reorder(2, 10, 3));
    printf("long_name_1(3, 4)        = %d (expect 7)\n", long_name_1(3, 4));
    printf("CamelCase(6, 7)          = %d (expect 42)\n", CamelCase(6, 7));
    return 0;
}

