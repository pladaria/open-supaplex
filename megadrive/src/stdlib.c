#include <stdlib.h>

void *calloc(size_t __nmemb, size_t __size)
{
    return malloc(__nmemb * __size);
}