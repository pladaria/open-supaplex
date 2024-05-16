#include "stdint.h"
#include "stdio.h"
#include "supaplex/globals.h"

void initializeSystem(void)
{
    kprintf("*** initializeSystem");
    kprintf("Init RAM check...");
    SRAM_enableRO();
    uint8_t sramHeaderCheckPass = 1;
    for (uint16_t i = 0; i < SRAM_HEADER_SIZE; i++)
    {
        if (SRAM_readByte(i) != SRAM_HEADER[i])
        {
            sramHeaderCheckPass = 0;
            break;
        }
    }
    if (!sramHeaderCheckPass)
    {
        kprintf("SRAM header check failed, initializing...");
        SRAM_enable();
        for (uint16_t i = 0; i < SRAM_HEADER_SIZE; i++)
        {
            SRAM_writeByte(i, SRAM_HEADER[i]);
        }
        for (uint16_t i = SRAM_HEADER_SIZE; i < SRAM_SIZE; i++)
        {
            SRAM_writeByte(i, 0);
        }
    } else {
        kprintf("SRAM check passed");
    }
    SRAM_disable();
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
