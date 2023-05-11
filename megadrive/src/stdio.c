#include <stdio.h>

int snprintf(char *str, size_t size, const char *format, ...)
{
    return 0;
}

int fprintf(FILE *stream, const char *format, ...)
{
    return 0;
}

int printf(const char *format, ...)
{
    return 0;
}

int vfprintf(FILE *stream, const char *format, ...)
{
    return 0;
}

long int ftell(FILE *stream)
{
    return 0;
}

int fseek(FILE *stream, long int offset, int whence)
{
    return 0;
}

int fclose(FILE *stream)
{
    return 0;
}

FILE *fopen(const char *filename, const char *mode)
{
    return NULL;
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    return 0;
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    return 0;
}