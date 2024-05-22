#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach-o/dyld.h>
#include <limits.h>
#include <sys/stat.h>

#include "dir.h"
#include "utils.h"
#include "logger.h"
#include "macros.h"

void trim_path(char* path)
{
    char *end = path + strlen(path) - 1;
    while (end > path && *end != '/')
        end--;

    end++;

    if (end > path)
        *end = '\0';
}

void project_path(char* buff, uint32_t size)
{
    /* Cross Platform implementation needed */
    if (getcwd(buff, size) == NULL) {
        perror("Error getting current working directory");
        exit(EXIT_FAILURE);
    }
}

int dir_exist(const char* path)
{
    printf("wd %s\n", path);
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;

    return S_ISDIR(statbuf.st_mode);
}

void init_git()
{
    print_info("Initializing Git...");
    run_command("git init");
    print_success("Git successfully created");
}

void init_config()
{
    print_info("Initializing Config File");

    FILE *file = fopen(CONFIG_PATH, "w");
    if (file == NULL)
    {
        perror("Error opening config file.");
        exit(0);
    }

    if (fprintf(file, "%s", CONFIG_INIT_CONTENT) < 0)
    {
        perror("Error writing file.");
        fclose(file);
        exit(0);
    }

    if (fclose(file) != 0) {
        perror("Error closing file.");
        exit(0);
    }

    print_success("Config file created.");
}