#include <stdlib.h>

/**
 * Converts the letter to lower case, if possible.
 */
char toupper(char ch)
{
    if (ch >= 'a' && ch <= 'z')
    {
        return ch - 0x20;
    }
    return ch;
}

/**
 * Searches for the first occurrence of the character c (an unsigned char) in the string pointed to by the argument str.
 */
char *strchr(const char *str, int c)
{
    while (*str != '\0')
    {
        if (*str == c)
        {
            return (char *)str;
        }
        str++;
    }
    return NULL;
}