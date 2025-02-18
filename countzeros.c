#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    char dev[1000];
    while ((scanf("%d", &n) > 0) &&
           (scanf("%s", &dev) > 0))
    {

        char* p = dev + 1;
        while (*p == '0')
            p++;

        printf(
            "%d %d \n", n, p - dev - 1);
    }

    exit(0);
}
