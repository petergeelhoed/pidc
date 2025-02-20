#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long gcd(long a, long b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

int main(int argc, char** argv)
{
    clock_t time_req = clock();

    int v = 0;
    long loop = 1;
    if (argc > 1)
    {
        loop = atoi(argv[1]);
    }
    if (argc > 2)
        v = atoi(argv[2]);
    for (long a = loop; a <= loop; a++)
    {
        long remainder = a;
        long n = 1;
        long t = 1;
        long count = 0;
        while (remainder != 1 && remainder != 0)
        {
            count++;
            long int nSquareA = n * n * a;
            t = sqrt(nSquareA) + 0.5;
            long int tSquare = t * t;
            remainder = tSquare - nSquareA;
            if (remainder == 0 || t == 0)
                break;
            long newt = tSquare + nSquareA;
            long trem = gcd(newt, a);
            long try = gcd(remainder, trem);

            if (v > 2)
                printf("TT %ld %ld %ld %ld %ld %ld\n",
                       a,
                       t,
                       n,
                       remainder,
                       trem,
                       try);

            if (try > 1 || remainder == -1)
            {
                count++;
                long newn = n * t * 2;
                long g = gcd(newt, newn);
                newt /= g;
                newn /= g;
                remainder = newt * newt - newn * newn * a;

                if (v > 1)
                    printf("TEST %ld %ld %ld %ld %ld %ld\n",
                           a,
                           newt,
                           newn,
                           remainder,
                           trem,
                           g);
                if (remainder == 1)
                {
                    n = newn;
                    t = newt;
                    break;
                }
            }
            n++;
        }
        if (t > 0)
        {
            printf("%ld %ld %ld %ld %ld\n", a, t, n, remainder, count);
        }
        else
        {
            printf("Error overflow!!!\n");
        }
    }
    printf("time= %lu/%lu\n", -time_req + clock(), CLOCKS_PER_SEC);

    exit(0);
}
