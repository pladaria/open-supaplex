#include <stddef.h>
#include "supaplex/config.h"

Config *initializeConfigForWriting(const char *pathname) {
    return NULL;
}

Config *initializeConfigForReading(const char *pathname) {
    return NULL;
}

void destroyConfig(Config *config) {}

void writeConfigSection(Config *config, const char *section) {}

void writeConfigInt(Config *config, const char *key, const int value){}

void writeConfigString(Config *config, const char *key, const char *value){}

int readConfigInt(Config *config, const char *section, const char *key, const int defaultValue) {
    return 0;
}

int readConfigString(Config *config, const char *section, const char *key, char *output) {
    return 0;
}
