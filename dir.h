#ifndef DIR_H
#define DIR_H

#include <stdbool.h>

int dir_exists(const char* path);
int file_exists(const char* path);
int exists(const char *path, bool is_directory);
void init_dir(const char *full_path);
void project_path(char *buff, uint32_t size);
void init_git();
void init_config();

#endif