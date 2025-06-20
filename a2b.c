#include <stdio.h>

int main(int argc, char** argv)
{
    int c = 29;
    int shifted;
    int one = 1;
    int result;
    while (c = getchar(), c != EOF) // && c != 10)
    {
        if (c == 10)
        {
            puts("");
        }
        else
        {
            char out[9] = "00000000";
            for (int pos = 0; pos < 8; pos++)
            {
                shifted = one << (pos);
                result = c & shifted;
                if (result == shifted)
                {
                    out[7 - pos] = '1';
                }
            }
            //        printf("%d %s\n", c, out);
            printf("%s ", out);
        }
    }
}
