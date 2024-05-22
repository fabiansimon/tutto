#ifndef CONFIG_H
#define CONFIG_H

#include "macros.h"

typedef struct {
    char name[CONFIG_LINE_BUFFER_SIZE/2];
    int interval; // In seconds
    char path[CONFIG_LINE_BUFFER_SIZE];
} Config;

int read_config(const char *filename, Config *config);

#endif