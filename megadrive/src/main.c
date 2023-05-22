#include "genesis.h"
#include "supaplex.h"

int main(bool hardReset) {
    if (!hardReset)
    {
        SYS_hardReset();
    }

    return supaplex_main(0, NULL);
}
