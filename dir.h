#ifndef DIR_H
#define DIR_H

void project_path(char *buff, uint32_t size);
int dir_exist(const char *path);
void init_git();
void init_config();

#endif