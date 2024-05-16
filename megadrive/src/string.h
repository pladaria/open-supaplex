#ifndef _STRING_H
#define _STRING_H 1

#include "stddef.h"

char *strerror(int errnum);
int memcmp(const void *str1, const void *str2, size_t n);

#endif