#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 64

char* stripZeros(char* in)
{
    size_t length = strlen(in);
    size_t offset = strspn(in, "0");
    if (length == offset)
    {
        in[1] = '\0';
    }
    else if (offset < length && offset > 0)
    {
        memmove(in, in + offset, length - offset);
        memset(in + length - offset, '\0', offset);
    }
    return in;
}

char* toArr(unsigned long int i)
{
    char* ret = (char*)calloc(SIZE + 1, sizeof(char));
    if (ret == NULL)
    {
        puts("no more memory");
        exit(-2);
    }

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
    size++;
    char* ret = (char*)calloc(size + 1, sizeof(char));
    if (ret == NULL)
    {
        puts("no more memory");
        exit(-2);
    }
    ret[size] = '\0';
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
    if (ret == NULL)
    {
        puts("no more memory");
        exit(-2);
    }
    ret[size] = '\0';
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
    if (ret == NULL)
    {
        puts("no more memory");
        exit(-2);
    }
    ret[size] = '\0';
    memset(ret, '0', size);

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
                (ret[size - indexout] - '0') + digit1 * digit2 + carry;
            carry = 0;
            outdigit += '0';
            while (outdigit > '9')
            {
                outdigit -= 10;
                carry += 1;
            }
            ret[size - indexout] = outdigit;
        }
        if (carry)
        {
            ret[size - indexout - 1] = '0' + carry;
            carry = 0;
        }
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
    if (works == NULL)
    {
        puts("no more memory");
        exit(-2);
    }
    char* result = (char*)calloc((size + 1), sizeof(char));
    if (result == NULL)
    {
        puts("no more memory");
        exit(-2);
    }

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
        tryArr = toArr(try);
        char* trySq = mulArr(tryArr, tryArr);
        if (greater(trySq, works) > 0)
        {
            try--;
            free(tryArr);
            free(trySq);
            break;
        }
        free(trySq);
        free(tryArr);
    }

    result[0] = try + '0';
    char* resSq = mulArr(result, result);
    char* newWorks = subArr(works, resSq);
    free(resSq);
    free(works);
    works = newWorks;
    char* arr20 = toArr(20);

    while (pos < size - 1)
    {
        size_t nullpos = strlen(works);
        works[nullpos] = in[pos++];
        works[nullpos + 1] = in[pos++];
        works[nullpos + 2] = '\0';

        char arrt[2] = "0";
        for (; arrt[0] < '9' + 1;)
        {
            char* mul20 = mulArr(arr20, result);
            char* sum20t = addArr(mul20, arrt);
            char* mulart = mulArr(sum20t, arrt);
            free(mul20);
            if (greater(mulart, works) > 0)
            {
                arrt[0] -= 1;
                free(sum20t);
                free(mulart);
                break;
            }
            free(sum20t);
            free(mulart);
            arrt[0] += 1;
        }
        char* res20 = mulArr(arr20, result);
        char* sum20 = addArr(res20, arrt);
        free(res20);
        char* mulart = mulArr(sum20, arrt);
        newWorks = subArr(works, mulart);
        free(sum20);
        free(mulart);
        free(works);
        works = newWorks;
        char* result10 = mulArr(result, "10");
        char* result10t = addArr(result10, arrt);
        free(result10);
        free(result);
        result = result10t;
    }
    free(arr20);
    free(works);

    return result;
}

char* closest(char* in)

{
    char* sqrt = sqrtArr(in);
    char* mularr = mulArr(sqrt, sqrt);
    char* diff0 = subArr(in, mularr);
    free(mularr);
    char* addone = addArr(sqrt, "1");
    char* mularr1 = mulArr(addone, addone);
    char* diff1 = subArr(mularr1, in);
    free(mularr1);
    if (greater(diff1, diff0) >= 0)
    {
        free(diff0);
        free(diff1);
        free(addone);
        return sqrt;
    }
    else
    {
        free(diff0);
        free(diff1);
        free(sqrt);
        return addone;
    };
}

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
