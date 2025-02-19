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
    long a = 2;
    if (argc > 1)
    {
        a = atoi(argv[1]);
    }
    long remainder = a;
    long n = 1;
    while (remainder != 1 && remainder != 0)
    {
        long t = sqrt(n * n * a) + 0.5;
        remainder = t * t - n * n * a;

        printf("TT %ld %ld %ld %ld %ld %ld\n",
               a,
               t,
               n,
               remainder,
               a,
               gcd(remainder, a));

        if (a % t == 0)
        {
            t = t + a / labs(remainder) * n * n;
            n = 2 * n;
            remainder = t * t - n * n * a;
            printf("%ld %ld %ld %ld\n", a, t, n, remainder);
            break;
        }
        if (remainder == 1)
        {
            printf("%ld %ld %ld %ld\n", a, t, n, remainder);
        }
        else if ((labs(remainder) == 2) || remainder == -1)
        {
            printf("from: %ld %ld %ld || ", t, n, remainder);
            long new = n* t * 2;
            t = t * t + n * a * n;
            n = new;
            long g = gcd(t, n);
            t /= g;
            n /= g;
            remainder = t * t - n * n * a;

            printf("%ld %ld %ld %ld\n", a, t, n, remainder);
            break;
        }
        else
        {
            n++;
        }
    }

    exit(0);
}
