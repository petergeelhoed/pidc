#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "libsqrt.h"

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        // puts(sqrtArr(argv[1]));
        char* sqrt = closest(argv[1]);
        char* val = mulArr(sqrt, sqrt);
        printf("%s %s %s\n", sqrt, val, argv[1]);

        free(val);
        free(sqrt);
    }

    return 0;
}
