#include "stdio.h"
#include "genesis.h"
#include "../res/resources.h"

int snprintf(char *str, size_t size, const char *format, ...)
{
    SYS_die("snprintf not implemented");
    return 0;
}

int fprintf(FILE *stream, const char *format, ...)
{
    SYS_die("fprintf not implemented");
    return 0;
}

int printf(const char *format, ...)
{
    SYS_die("printf not implemented");
    return 0;
}

int vfprintf(FILE *stream, const char *format, ...)
{
    SYS_die("vfprintf not implemented");
    return 0;
}

long int ftell(FILE *stream)
{
    SYS_die("ftell not implemented");
    return 0;
}

int fseek(FILE *stream, long int offset, int whence)
{
    SYS_die("fseek not implemented");
    return 0;
}

int fclose(FILE *stream)
{
    kprintf("fclose '%s'", stream->name);
    if (stream != NULL)
    {
        MEM_free(stream);
        MEM_pack();
        kprintf("MEM_getFree: %d", MEM_getFree());
        kprintf("MEM_getLargestFreeBlock: %d", MEM_getLargestFreeBlock());
    }
    return 0;
}

FILE *fopen(const char *filename, const char *mode)
{
    kprintf("fopen '%s'; '%s'", filename, mode);
    if (strcmp("LEVEL.LST", filename) == 0)
    {
        FILE *file = MEM_alloc(sizeof(FILE));
        strcpy(file->name, filename); // @TODO pladaria: remove, this is for debug purposes
        file->position = 0;
        file->data = binLevelLst;
        return file;
    }
    return NULL;
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    SYS_die("fwrite not implemented");
    return 0;
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    kprintf("fread '%s'; %lu bytes", stream->name, nmemb);
    // @TODO pladaria: remove check if not needed
    if (size != 1)
    {
        SYS_die("fread size != 1");
    }
    memcpy(ptr, stream->data + stream->position, nmemb);
    stream->position += nmemb;
    return nmemb;
}