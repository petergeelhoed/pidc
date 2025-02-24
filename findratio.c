#include <limits.h>
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
    long a = 1;
    if (argc > 1)
    {
        a = atoi(argv[1]);
    }
    if (argc > 2)
        v = atoi(argv[2]);
    unsigned long maxn = sqrt(ULONG_MAX / a);
    unsigned long maxt = sqrt(ULONG_MAX);
    long remainder = a;
    // unsigned long n = 182475670;
    unsigned long n = 1;
    unsigned long t = 0;
    unsigned long count = 0;
    while (remainder != 1 && remainder != 0)
    {
        if (n > maxn || t > maxt)
        {
            printf("Overflow %lu %lu\n", n, t);

            exit(-15);
        }
        count++;
        long unsigned int nSquareA = n * n * a;
        t = sqrt(nSquareA) + 0.5;
        long unsigned int tSquare = t * t;

        remainder = tSquare - nSquareA;
        if (remainder == 0)
            break;
        unsigned long newt = tSquare + nSquareA;
        if (newt < tSquare)
        {
            printf("Overflow SQ %lu %lu %lu %lu \n", n, t, newt, tSquare);

            exit(-15);
        }
        long unsigned newn = n * t * 2;
        if (v > 2)
            printf("TT %ld %lu %lu %ld %lu %ld %lu %lu %lu\n",
                   a,
                   t,
                   n,
                   remainder,
                   labs(remainder),
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
                printf(
                    "TEST %ld %ld %ld %ld %ld\n", a, newt, newn, remainder, g);
            if (remainder == 1)
            {
                n = newn;
                t = newt;
                break;
            }
            else
            {
                // this should never happen.
                printf("NO GO: %ld %ld %ld %ld %lu\n",
                       a,
                       newt,
                       newn,
                       remainder,
                       n);
                exit(1);
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
    if (v > 3)
        printf("time= %lu/%lu\n", -time_req + clock(), CLOCKS_PER_SEC);

    exit(0);
}
