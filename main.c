#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>

#include "config.h"
#include "utils.h"
#include "dir.h"
#include "logger.h"

int main() 
{
    Config config;

    char wd[PATH_MAX];
    project_path(wd, sizeof(wd));

    strncpy(config.path, wd, sizeof(config.path));

    char *git_dir = concat_strs(config.path, "/", ".git", NULL);
    char *snap_dir = concat_strs(config.path, "/", SNAP_DIRECTORY_NAME, NULL);
    char *config_file = concat_strs(config.path, "/", CONFIG_PATH, NULL);

    const char *timestamp = unix_timestamp();
    char *snap_file_path = concat_strs(snap_dir, "/", timestamp);
    run_command_file("git diff", snap_file_path);

    return 0; 

    /* Check if Tutu config file exists */
    if (dir_exist(config_file) == 0)
    {
        print_error("No config file found. Press Y to initialize one.");

        char input[3];
        if (!binary_input(input, sizeof(input), "Y"))
            exit(0);

        init_config();
    }

    /* Check if Git is already initalized */
    if (dir_exist(git_dir) == 0)
    {
        print_error("Git not found, run \"git init\" or allow us to initialize a git directory by pressing \"Y\".");

        char input[3];
        if (!binary_input(input, sizeof(input), "Y"))
            exit(0);

        init_git();
    }

    /* Create hidden .tutu_snap file if none exists */
    if (dir_exist(snap_dir) == 0)
        init_dir(snap_dir);

    read_config(CONFIG_PATH, &config);

    for (;;) 
    {
        printf("Called, now timeout for %d seconds.\n", config.interval);

        timeout(config.interval);
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