#include <stdint.h>
#include "genesis.h"

void initializeSystem(void)
{
}

void destroySystem(void)
{
}

uint8_t isOld3DSSystem(void)
{
    return 0;
}

void exitWithError(const char *format, ...)
{
    char buffer[256];
    strcpy(buffer, format);
    SYS_die(buffer);
}

void handleSystemEvents(void)
{
}

uint32_t getTicks(void)
{
    // returns time in 1/256 seconds
    return getTime(0);
}

void waitTime(uint32_t time)
{
}
