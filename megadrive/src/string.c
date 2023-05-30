#include <string.h>
#include <stddef.h>

char *strerror(int errnum) {
    return "";
}

int memcmp(const void *str1, const void *str2, size_t n)
{
    const unsigned char *s1 = str1;
    const unsigned char *s2 = str2;
    while (n-- > 0)
    {
        if (*s1++ != *s2++)
        {
            return s1[-1] < s2[-1] ? -1 : 1;
        }
    }
    return 0;
}