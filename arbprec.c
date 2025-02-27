#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 64

char* stripZeros(char* in)
{
    size_t length = strlen(in);
    size_t offset = strspn(in, "0");
    //   printf("%lu %lu\n", length, offset);
    if (length == offset)
    {
        in[1] = '\0';
    }
    else if (offset < length && offset > 0)
    {
        memmove(in, in + offset, length - offset);
        memset(in + length - offset, '\0', length - offset);
    }
    return in;
}

char* toArr(unsigned long int i)
{
    char* ret = (char*)calloc(SIZE + 1, sizeof(char));

    snprintf(ret, SIZE, "%lu", i);
    return ret;
}

char* subArr(char* one, char* two)
{
    size_t len1 = strlen(one);
    size_t len2 = strlen(two);
    size_t size = len1 > len2 ? len1 : len2;

    // add one zero to see overflow
    size++;
    char* ret = (char*)calloc(size + 1, sizeof(char));
    ret[size + 1] = '\0';
    memset(ret, '0', size);

    char carry = 0;
    for (size_t index = 1; index <= size; ++index)
    {
        char digit1 = (index <= len1) ? one[len1 - index] : '0';
        char digit2 = (index <= len2) ? two[len2 - index] : '0';
        char outdigit = digit1 - digit2 + carry + '0';

        carry = 0;
        while (outdigit < '0')
        {
            outdigit += 10;
            carry -= 1;
        }
        ret[size - index] = outdigit;
    }
    return stripZeros(ret);
}

char* addArr(char* one, char* two)
{
    size_t len1 = strlen(one);
    size_t len2 = strlen(two);
    size_t size = len1 > len2 ? len1 : len2;

    // add one to size as it may be needed
    size++;
    char* ret = (char*)calloc(size + 1, sizeof(char));
    ret[size + 1] = '\0';
    memset(ret, '0', size);

    char carry = 0;
    for (size_t index = 1; index <= size; ++index)
    {
        char digit1 = (index <= len1) ? one[len1 - index] - '0' : 0;
        char digit2 = (index <= len2) ? two[len2 - index] - '0' : 0;
        char outdigit = digit1 + digit2 + carry + '0';

        carry = 0;
        while (outdigit > '9')
        {
            outdigit -= 10;
            carry += 1;
        }
        ret[size - index] = outdigit;
    }
    return stripZeros(ret);
}

char* mulArr(char* one, char* two)
{
    size_t len1 = strlen(one);
    size_t len2 = strlen(two);
    size_t size = len1 + len2;
    char* ret = (char*)calloc(size + 1, sizeof(char));
    ret[size] = '\0';
    memset(ret, '0', size - 1);

    char carry = 0;
    size_t indexout = 0;
    for (size_t index1 = 0; index1 < len1; ++index1)
    {
        for (size_t index2 = 0; index2 < len2; ++index2)
        {
            indexout = index1 + index2 + 1;
            char digit1 = one[len1 - index1 - 1] - '0';
            char digit2 = two[len2 - index2 - 1] - '0';

            char outdigit =
                (ret[size - indexout - 1] - '0') + digit1 * digit2 + carry;
            carry = 0;
            outdigit += '0';
            while (outdigit > '9')
            {
                outdigit -= 10;
                carry += 1;
            }
            ret[size - indexout - 1] = outdigit;
        }
    }
    if (carry)
    {
        size_t retlen = strlen(ret);
        memmove(ret + 1, ret, retlen + 1);
        ret[0] = '0' + carry;
    }

    return stripZeros(ret);
}

int greater(char* arr1, char* arr2)
{
    char* start1 = stripZeros(arr1);
    char* start2 = stripZeros(arr2);

    if (strlen(start1) > strlen(start2))
    {
        return 1;
    }
    if (strlen(start2) > strlen(start1))
    {
        return -1;
    }
    return strcmp(start1, start2);
}

char* sqrtArr(char* in)
{
    // add one to size as it may be needed
    size_t length = strlen(in);

    size_t size = length + length % 2;
    int try = 0;
    char* works = (char*)calloc((size + 1), sizeof(char));
    char* result = (char*)calloc((size + 1), sizeof(char));

    size_t pos = 0;

    if (length % 2 == 0)
    {
        works[0] = in[pos++];
        works[1] = in[pos++];
    }
    else
    {
        works[0] = in[pos++];
    }

    char* tryArr = NULL;
    for (; try < 10;)
    {
        try++;
        free(tryArr);
        tryArr = toArr(try);
        if (greater(mulArr(tryArr, tryArr), works) > 0)
        {
            try--;
            break;
        }
    }

    result[0] = try + '0';
    char* newWorks = subArr(works, mulArr(result, result));
    works = newWorks;

    while (pos < size - 1)
    {
        size_t nullpos = strlen(works);
        works[nullpos] = in[pos++];
        works[nullpos + 1] = in[pos++];
        works[nullpos + 2] = '\0';

        size_t t = 0;
        for (; t < 10UL; t++)
        {
            if (greater(mulArr(addArr(mulArr(toArr(20), result), toArr(t)),
                               toArr(t)),
                        works) > 0)
            {
                t--;
                break;
            }
        }
        newWorks = subArr(
            works,
            mulArr(addArr(mulArr(toArr(20), result), toArr(t)), toArr(t)));
        free(works);
        works = newWorks;
        size_t reslen = strlen(result);
        result[reslen] = t + '0';
    }

    return result;
}

char* closest(char* in)

{
    char* sqrt = sqrtArr(in);
    char* diff0 = subArr(in, mulArr(sqrt, sqrt));
    char* addone = addArr(sqrt, "1");
    char* diff1 = subArr(mulArr(addone, addone), in);
    return (greater(diff1, diff0) >= 0) ? sqrt : addone;
}

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        // puts(sqrtArr(argv[1]));
        puts(closest(argv[1]));
    }

    return 0;
}
