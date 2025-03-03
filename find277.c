#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "libsqrt.h"

int main()
{
    char a[201] = "277";
    /*"00000000000000000000000000000000000000000000000000000000000"
    "0000000000000000000000000000000000000"
    "0000000000000000000000000000000000000"
    "0000000000000000000000000000000000000000000000000000000000000";*/

    char* n = malloc(20 * sizeof(int));
    strncpy(n, "535974744", 20);
    int loop = 1;
    while (loop)
    {
        char* newN = addArr(n, "1");
        free(n);
        n = newN;
        // char* n = sqrtArr(toArr(ULONG_MAX));
        char* sq = mulArr(n, n);
        char* sqa = mulArr(sq, a);
        char* t = closest(sqa);
        char* tt = mulArr(t, t);

        char* remainder1 = subArr(tt, sqa);
        char* remainder2 = subArr(sqa, tt);
        if (loop % 10000 == 0)
        {
            loop = 1;
            puts(n);
            // puts(remainder1);
            // puts(remainder2);
        }
        if (strcmp(remainder1, "1") == 0 || strcmp(remainder2, "1") == 0 ||
            strcmp(remainder1, "2") == 0 || strcmp(remainder2, "2") == 0)
        {
            puts("found");
            puts(n);
            puts(t);
            puts(sqa);
            puts(tt);
            puts(remainder1);
            puts(remainder2);
            puts("");

            sq = mulArr(n, n);
            sqa = mulArr(sq, a);
            tt = mulArr(t, t);
            char* t2 = addArr(sqa, tt);
            puts(t2);
            n = mulArr(n, "2");
            n = mulArr(n, t);
            puts(n);
            break;
        }

        free(sq);
        free(sqa);
        free(t);
        free(tt);
        free(remainder1);
        free(remainder2);
        loop++;
    }
    free(n);
}
