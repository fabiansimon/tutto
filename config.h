#ifndef CONFIG_H
#define CONFIG_H

#include "macros.h"

typedef struct {
    char project_name[CONFIG_LINE_BUFFER_SIZE/2];
    int interval_sec;
} Config;

int read_config(const char *filename, Config *config);

#endif