#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

char* trim(char* val) 
{
    while (*val == ' ')
        val++;

    char *end = val + strlen(val) - 1;
    while (end > val && *end == ' ')
        end--;

    *(end + 1) = '\0'; // Write new null terminator
    return val;
}

int read_config(const char *filename, Config *config) 
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening *.tutu file");
        return -1;
    }

    char line[CONFIG_LINE_BUFFER_SIZE];
    while (fgets(line, sizeof(line), file)) 
    {
        if (line[0] == '#' || line[0] == '\n')
            continue;

        /* find "=" */
        char *delimiter = strchr(line, '=');
        if (delimiter == NULL)
        {
            fprintf(stderr, "Invalid .tutu config line: %s.\n", line);
            continue;
        }

        *delimiter = '\0';
        char *key = trim(line);
        char *val = trim(delimiter + 1);

        val[strcspn(val, "\n")] = '\0'; /* Remove newline if present */

        if (strcmp(key, "INTERVAL_SECONDS") == 0)
            config->interval = atoi(val);
        else if (strcmp(key, "PROJECT_NAME") == 0)
            strncpy(config->name, val, sizeof(config->name));
    }

    fclose(file);
    return 0;
}