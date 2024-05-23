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
#include "tutu.h"

int main() 
{
    Config config;

    char wd[PATH_MAX];
    project_path(wd, sizeof(wd));

    strncpy(config.path, wd, sizeof(config.path));

    char *git_dir = concat_strs(config.path, "/", ".git", NULL);
    char *snap_dir = concat_strs(config.path, "/", SNAP_DIRECTORY_NAME, NULL);
    char *config_file = concat_strs(config.path, "/", CONFIG_PATH, NULL);

    /* Check if Tutu config file exists */
    if (file_exists(config_file) == 0)
    {
        print_error("No config file found. Press Y to initialize one.");

        char input[3];
        if (!binary_input(input, sizeof(input), "Y"))
            exit(0);

        init_config();
    }

    /* Check if Git is already initalized */
    if (dir_exists(git_dir) == 0)
    {
        print_error("Git not found, run \"git init\" or allow us to initialize a git directory by pressing \"Y\".");

        char input[3];
        if (!binary_input(input, sizeof(input), "Y"))
            exit(0);

        init_git();
    }

    /* Create hidden .tutu_snap file if none exists */
    if (dir_exists(snap_dir) == 0)
        init_dir(snap_dir);

    read_config(CONFIG_PATH, &config);

    for (;;) 
    {
        printf("Called, now timeout for %d seconds.\n", config.interval);
        take_snap(snap_dir);
        timeout(config.interval);
    }

    return 0;
}