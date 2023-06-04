#include "stdio.h"
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
        file->start = 0;
        file->position = 0;
        file->data = binLevelLst;
        file->writeable = 0;
        return file;
    }
    if (strcmp("PLAYER.LST", filename) == 0)
    {
        SRAM_enableRO();
        uint8_t firstByte = SRAM_readByte(PLAYERS_LIST_OFFSET);
        SRAM_disable();
        if (firstByte == 0)
        {
            kprintf("PLAYER.LST not initialized");
            return NULL;
        }
        FILE *file = MEM_alloc(sizeof(FILE));
        strcpy(file->name, filename); // @TODO pladaria: remove, this is for debug purposes
        file->start = PLAYERS_LIST_OFFSET;
        file->position = 0;
        file->data = NULL;
        file->writeable = 1;
        return file;
    }
    kprintf("FILE NOT HANDLED: '%s'", filename);
    return NULL;
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    kprintf("*** fwrite '%s'; %lu bytes", stream->name, nmemb);
    if (!stream->writeable)
    {
        kprintf("FILE NOT WRITEABLE: '%s'", stream->name);
        return 0;
    }
    else
    {
        kprintf("Write to SRAM: '%s'", stream->name);
        SRAM_enable();
        for (uint16_t i = 0; i < nmemb; i++)
        {
            SRAM_writeByte(stream->start + stream->position + i, ((uint8_t *)ptr)[i]);
        }
        SRAM_disable();
        return nmemb;
    }
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    if (stream = NULL) {
        SYS_die("fread stream is NULL");
    }
    if (stream->writeable == 1)
    {
        return 0;
    }
    else
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
}