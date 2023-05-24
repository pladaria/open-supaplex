#include "genesis.h"
#include "supaplex.h"

int main(bool hardReset)
{
    if (!hardReset)
    {
        SYS_hardReset();
    }
    KLog("Starting Supaplex");
    KLog_U1("MEM_getFree: ", MEM_getFree());
    KLog_U1("MEM_getLargestFreeBlock: ", MEM_getLargestFreeBlock());

    return supaplex_main(0, NULL);
}
