#include "genesis.h"
#include "supaplex.h"
#include "supaplex/globals.h"

int main(bool hardReset)
{
    if (!hardReset)
    {
        SYS_hardReset();
    }
    kprintf("*** Starting Supaplex");
    kprintf("MEM_getFree: %d", MEM_getFree());
    kprintf("MEM_getLargestFreeBlock: %d", MEM_getLargestFreeBlock());
    kprintf("SRAM_SIZE: %lu", rom_header.sram_end - rom_header.sram_start);
    kprintf(gPlayerLstFilename);
    return supaplex_main(0, NULL);
}
