#ifndef _STDIO_H
#define _STDIO_H 1

#include "stddef.h"

#define SRAM_HEADER "SUPAPLEX-002"
#define SRAM_HEADER_SIZE sizeof(SRAM_HEADER)

#define PLAYERS_LIST_OFFSET SRAM_HEADER_SIZE
#define PLAYERS_LIST_SIZE sizeof(gPlayerListData)

#define HALL_OF_FAME_OFFSET PLAYERS_LIST_OFFSET + PLAYERS_LIST_SIZE
#define HALL_OF_FAME_SIZE sizeof(gHallOfFameData)

#define SRAM_SIZE PLAYERS_LIST_OFFSET + PLAYERS_LIST_SIZE + HALL_OF_FAME_SIZE

typedef struct FILE {
    char name[16];
    uint16_t start;
    uint16_t position;
    const uint8_t *data;
    uint8_t writeable; // if true, uses SRAM
} FILE;

#define stderr NULL

#define SEEK_SET 0 /* Seek from beginning of file. */
#define SEEK_END 2 /* Seek from end of file. */

int snprintf(char *str, size_t size, const char *format, ...);
int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int vfprintf(FILE *stream, const char *format, ...);

long int ftell(FILE *stream);
int fseek(FILE *stream, long int offset, int whence);
int fclose(FILE *stream);
FILE *fopen(const char *filename, const char *mode);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

#endif