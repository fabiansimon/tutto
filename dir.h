#ifndef DIR_H
#define DIR_H

int dir_exist(const char *path);
void init_dir(const char *full_path);
void project_path(char *buff, uint32_t size);
void init_git();
void init_config();

#endif