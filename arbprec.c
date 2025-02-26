#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

char* stripZeros(char* in) { return in + strspn(in, "0"); }

char* toArr(unsigned long int i, size_t size)
{
    char* ret = (char*)calloc(size + 1, sizeof(char));
    memset(ret, '0', size);
    ret[size + 1] = '\0';

    size_t pos = 0;
    while (i > 0)
    {
        if (pos > size)
        {
            printf("out of bounds\n");
            exit(-1);
        }
        ret[size - pos] = i % 10 + '0';
        pos++;
        i /= 10;
    }

    return ret;
}

char* subArr(char* one, char* two, size_t size)
{
    char* ret = (char*)calloc(size + 1, sizeof(char));
    ret[size + 1] = '\0';
    memset(ret, '0', size);

    char carry = 0;
    for (size_t index = 0; index < size; ++index)
    {
        char digit1 = one[size - index];
        char digit2 = two[size - index] - '0';
        char outdigit = digit1 - digit2 + carry;
        carry = 0;
        while (outdigit < '0')
        {
            outdigit += 10;
            carry -= 1;
        }
        ret[2 * size - 1 - index] = outdigit;
    }
    return ret;
}
char* addArr(char* one, char* two, size_t size)
{
    char* ret = (char*)calloc(2 * size + 1, sizeof(char));
    ret[size * 2 + 1] = '\0';
    memset(ret, '0', size * 2);

    char carry = 0;
    for (size_t index = 0; index < size; ++index)
    {
        char digit1 = one[size - index];
        char digit2 = two[size - index] - '0';
        char outdigit = digit1 + digit2 + carry;
        carry = 0;
        while (outdigit > '9')
        {
            outdigit -= 10;
            carry += 1;
        }
        ret[2 * size - 1 - index] = outdigit;
    }
    return ret;
}

char* mulArr(char* one, char* two, size_t size)
{
    char* ret = (char*)calloc(2 * size + 1, sizeof(char));
    ret[size * 2 + 1] = '\0';
    memset(ret, '0', size * 2);

    char carry = 0;
    for (size_t index1 = 0; index1 < size; ++index1)
    {
        size_t indexout = 0;
        for (size_t index2 = 0; index2 < size; ++index2)
        {
            indexout = index1 + index2;
            char digit1 = one[size - index1] - '0';
            char digit2 = two[size - index2] - '0';

            char outdigit =
                (ret[2 * size - 1 - indexout] - '0') + digit1 * digit2 + carry;
            carry = 0;
            outdigit += '0';
            while (outdigit > '9')
            {
                outdigit -= 10;
                carry += 1;
            }
            ret[2 * size - 1 - indexout] = outdigit;
        }
    }
    return ret;
}

int greater(char* arr1, char* arr2)
{
    char* start1 = stripZeros(arr1);
    char* start2 = stripZeros(arr2);
    return strcmp(start1, start2);
}

char* sqrtArr(char* in)
{
    size_t size = strlen(in);
    char* val = stripZeros(in);
    size_t length = strlen(val);
    size_t pos = size - length - length % 2;
    int try = 0;
    char* works = (char*)malloc((size + 1) * sizeof(char));
    memset(works, '0', size);
    works[size + 1] = '\0';
    strncpy(works + size - 2, in + pos, 2);
    printf("%s\n", works);

    char digit1 = in[pos++] - '0';
    char digit2 = in[pos++] - '0';
    int work = digit1 * 10 + digit2;
    char* tryarr;
    for (; try < 10;)
    {
        try++;
        tryarr = toArr(try, size);
        char* tryarr = toArr(try, size);
        if (greater(mulArr(tryarr, tryarr, size), works) > 0)
        {
            try--;
            break;
        }
    }
    free(tryarr);
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

    free(works);
    return toArr(result, size);
}

int main()
{

    char* two = toArr(21355, SIZE);
    char* one = toArr(21351, SIZE);
    char* ret = mulArr(one, two, SIZE);
    char* sub1 = addArr(two, one);
    printf("%s\n", sub1);
    char* sub = addArr(one, two);
    printf("%s\n", sub);
    char* add = addArr(one, two);
    printf("%s\n", add);

    printf("%s\n", one);
    printf("%s\n", two);
    printf("%s\n", ret);
    printf("%s\n", stripZeros(ret));
    printf("%d\n", greater(one, two));
    printf("%d\n", greater(two, one));
    printf("%d\n", greater(one, one));
    printf("OUT: %s\n", sqrtArr(ret));

    free(one);
    free(two);
    free(ret);
    return 0;
}
