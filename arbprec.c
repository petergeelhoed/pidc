#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

char* stripZeros(char* in) { return in + strspn(in, "0"); }

char* toArr(unsigned long int i)
{
    char* ret = (char*)calloc(SIZE + 1, sizeof(char));
    memset(ret, '0', SIZE);
    ret[SIZE + 1] = '\0';

    size_t pos = 0;
    while (i > 0)
    {
        if (pos > SIZE)
        {
            printf("out of bounds\n");
            exit(-1);
        }
        ret[SIZE - pos] = i % 10 + '0';
        pos++;
        i /= 10;
    }

    return ret;
}

char* addArr(char* one, char* two)
{
    char* ret = (char*)calloc(2 * SIZE + 1, sizeof(char));
    ret[SIZE * 2 + 1] = '\0';
    memset(ret, '0', SIZE * 2);

    char carry = 0;
    for (size_t index = 0; index < SIZE; ++index)
    {
        char digit1 = one[SIZE - index];
        char digit2 = two[SIZE - index] - '0';
        char outdigit = digit1 + digit2 + carry;
        carry = 0;
        while (outdigit > '9')
        {
            outdigit -= 10;
            carry += 1;
        }
        ret[2 * SIZE - 1 - index] = outdigit;
    }
    return ret;
}
char* mulArr(char* one, char* two)
{
    char* ret = (char*)calloc(2 * SIZE + 1, sizeof(char));
    ret[SIZE * 2 + 1] = '\0';
    memset(ret, '0', SIZE * 2);

    char carry = 0;
    for (size_t index1 = 0; index1 < SIZE; ++index1)
    {
        size_t indexout = 0;
        for (size_t index2 = 0; index2 < SIZE; ++index2)
        {
            indexout = index1 + index2;
            char digit1 = one[SIZE - index1] - '0';
            char digit2 = two[SIZE - index2] - '0';

            char outdigit =
                (ret[2 * SIZE - 1 - indexout] - '0') + digit1 * digit2 + carry;
            carry = 0;
            outdigit += '0';
            while (outdigit > '9')
            {
                outdigit -= 10;
                carry += 1;
            }
            ret[2 * SIZE - 1 - indexout] = outdigit;
        }
    }
    return ret;
}

char* sqrtArr(char* in)
{
    size_t size = strlen(in);
    char* val = stripZeros(in);
    size_t length = strlen(val);
    printf("V %lu\n", length);
    size_t pos = size - length - length % 2;
    printf("V %lu %lu\n", size, pos);
    printf("V %s\n", in + pos);
    int try = 0;
    char digit1 = in[pos++] - '0';
    char digit2 = in[pos++] - '0';
    int work = digit1 * 10 + digit2;
    for (size_t i = 0; i < 10; i++)
    {
        try++;
        if (try * try > work)
        {
            try--;
            break;
        }
    }
    printf("%d %d\n", work, try);
    int result = try;
    work = work - try * try;
    while (pos < size)
    {
        work *= 100;
        work += 10 * (in[pos++] - '0');
        work += in[pos++] - '0';
        //   printf("work %d\n", work);
        int t = 0;
        for (size_t i = 0; i < 10; i++)
        {
            t++;
            //     printf("work %d*%d < %d \n", 20 * result + t, t, work);
            if ((20 * result + t) * t > work)
            {
                t--;
                break;
            }
        }
        //       printf("calv %d %d %d\n", 20 * result + t, work, t);
        work = work - (20 * result + t) * t;
        result *= 10;
        result += t;
        //      printf("resu %d %d %d\n", result, work, t);
    }

    return toArr(result);
}

int main()
{

    char* two = toArr(21355);
    char* one = toArr(21355);
    char* ret = mulArr(one, two);
    // char* ret = addArr(one, two);
    printf("%s\n", one);
    printf("%s\n", two);
    printf("%s\n", ret);
    printf("%s\n", stripZeros(ret));
    printf("OUT: %s\n", sqrtArr(ret));
    free(one);
    free(two);
    free(ret);
    return 0;
}
