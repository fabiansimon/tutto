#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>

#include "config.h"
#include "utils.h"
#include "tutto.h"

#define CONFIG_PATH "config.ttu"

void run_command(const char* cmd) 
{
    system(cmd);
}

int main() 
{
    Config config;
    read_config(CONFIG_PATH, &config);

    char wd[PATH_MAX];
    total_path(wd, sizeof(wd));

    for (;;) 
    {
        printf("Called, now timeout for %d seconds.\n", config.interval_sec);
        timeout(config.interval_sec);
    }

    /*
    char *timestamp = unix_timestamp();
    if (timestamp == NULL)
        return 1;

    char interval_str[20];
    snprintf(interval_str, sizeof(interval_str), "%d", config.interval_mins);

    char *full_cmd = concat_strs("echo \"timestamp: ", timestamp, "\nInterval: ", interval_str, "\nProject Name: ", config.project_name, "\"", NULL);

    if (full_cmd != NULL) {
        run_command(full_cmd);
        free(full_cmd);
    }
    */

    return 0;
}