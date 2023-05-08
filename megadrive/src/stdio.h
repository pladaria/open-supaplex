#ifndef _STDIO_H
#define _STDIO_H 1

#include <stddef.h>

struct _IO_FILE;
typedef struct _IO_FILE FILE;

#define SEEK_SET 0 /* Seek from beginning of file. */
#define SEEK_END 2 /* Seek from end of file. */

int snprintf(char *str, size_t size, const char *format, ...);
int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);

long int ftell(FILE *stream);
int fseek(FILE *stream, long int offset, int whence);
int fclose(FILE *stream);

#endif