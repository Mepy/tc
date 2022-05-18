struct A
{
    long x;
    double y;
    char c[2];
    A(long x, double y)
    :x(x), y(y){
        c[0] = 'x';
        c[1] = 'y';
    }
};
#include <cstdio>

int main()
{
    long _;
    scanf("%ld\n", &_);
    A x(_, 2.0);
    printf("%ld\n", x.x);
}