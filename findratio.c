#include <math.h>
#include <stdio.h>
#include <stdlib.h>

long gcd(long a, long b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

int main(int argc, char** argv)
{
    int v = 1;
    long a = 2;
    if (argc > 1)
    {
        a = atoi(argv[1]);
    }
    long remainder = a;
    long n = 1;
    long t = 1;
    while (remainder != 1 && remainder != 0)
    {
        t = sqrt(n * n * a) + 0.5;
        remainder = t * t - n * n * a;
        long grem = gcd(remainder, a);
        long trem = gcd(t * t + a * n * n, a);
        if (v)
            printf("TT %ld %ld %ld %ld %ld %ld %ld\n",
                   a,
                   t,
                   n,
                   remainder,
                   a,
                   grem,
                   trem);

        if (trem == -1 || labs(trem) > 1 || (labs(remainder) == 2) ||
            remainder == -1)
        {
            long newn = n * t * 2;
            long newt = (t * t + n * a * n);
            long g = gcd(newt, newn);
            newt /= g;
            newn /= g;
            remainder = newt * newt - newn * newn * a;

            if (v)
                printf("TEST %ld %ld %ld %ld %ld %ld %ld\n",
                       a,
                       newt,
                       newn,
                       remainder,
                       g,
                       grem,
                       trem);
            if (remainder == 1)
            {
                n = newn;
                t = newt;
                break;
            }
        }
        n++;
    }
    printf("%ld %ld %ld %ld\n", a, t, n, remainder);

    exit(0);
}
