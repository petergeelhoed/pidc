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
        // long n = 408028012;
        long n = 1;
        long t = 0;
        long count = 0;
        while (remainder != 1 && remainder != 0)
        {
            // if (n > 408028016) break;
            count++;
            long unsigned int nSquareA = n * n * a;
            t = sqrt(nSquareA) + 0.5;
            long unsigned int tSquare = t * t;
            remainder = tSquare - nSquareA;
            if (remainder == 0)
                break;
            unsigned long newt = tSquare + nSquareA;
            long unsigned newn = n * t * 2;

            if (v > 2)
                printf("TT %ld %ld %ld %ld %ld %lu %lu %ld\n",
                       a,
                       t,
                       n,
                       remainder,
                       newn % labs(remainder),
                       tSquare,
                       nSquareA,
                       newt);

            if (newn % labs(remainder) == 0)
            {
                count++;
                long g = gcd(newt, newn);
                newt /= g;
                newn /= g;
                remainder = newt * newt - newn * newn * a;

                if (v > 1)
                    printf("TEST %ld %ld %ld %ld %ld\n",
                           a,
                           newt,
                           newn,
                           remainder,
                           g);
                if (remainder == 1)
                {
                    n = newn;
                    t = newt;
                    break;
                }
                else
                {
                    // this should never happen.
                    printf("NO GO: % ld % ld % ld % ld % ld\n ",
                           a,
                           newt,
                           newn,
                           remainder,
                           g);
                }
            }
            n++;
            if (t == 1)
            {
                printf("%ld %ld %ld %ld %ld\n", a, t, n, remainder, count);
            }
        }
        if (t > 0 || a == 0)
        {
            printf("%ld %ld %ld %ld %ld\n", a, t, n, remainder, count);
        }
        else
        {
            printf("Error overflow!!!\n");
        }
    }
    if (v > 3)
        printf("time= %lu/%lu\n", -time_req + clock(), CLOCKS_PER_SEC);

    exit(0);
}
