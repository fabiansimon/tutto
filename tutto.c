#include <sys/stat.h>

#include "tutto.h"

int dir_exist(const char* path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;

    return S_ISDIR(statbuf.st_mode);
}