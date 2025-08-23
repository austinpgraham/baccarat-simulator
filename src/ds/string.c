#include <stdlib.h>
#include "ds/string.h"

int str_equal(const char *str1, const char *str2)
{
    if (str1 == NULL && str2 == NULL)
    {
        return 1;
    }

    int i = 0;
    int j = 0;

    while ((str1[i] == str2[j]) && (str1[i] != '\0' && str2[j] != '\0'))
    {
        i++;
        j++;
    }

    return i == j && str1[i] == str2[j];
}

int str_to_int(const char *str)
{
    if (str == NULL || str[0] == '\0')
    {
        return 0;
    }

    int total = 0;

    int i = 0;
    // Skip any initial whitespace
    while (str[i] == ' ')
    {
        i++;
    }

    do
    {
        char c = str[i];
        int ascii_value = c - 48;
        // Die if we encounter anything that's not a digit.
        if (ascii_value < 0 || ascii_value > 9)
            break;
        total = (total * 10) + ascii_value;
    } while (str[++i] != '\0');

    return total;
}
