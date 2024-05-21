#ifndef UTILS_H
#define UTILS_H

char *concat_strs(const char *first, ...);
char *unix_timestamp();
void timeout(int seconds);
void total_path(char *buff, size_t size);

#endif