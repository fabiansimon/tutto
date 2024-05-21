#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <limits.h>
#endif


#include "utils.h"

#define TIMESTAMP_LENGTH 20

char* concat_strs(const char* first, ...)
{
    va_list args;
    const char *str;
    size_t length = strlen(first);

    /* Calculate total length of args */
    va_start(args, first);
    while ((str = va_arg(args, const char*)) != NULL)
    {
        length += strlen(str);
    }
    va_end(args);

    /* Allocate memory for resulted string */
    char *res = (char *)malloc(length + 1);
    if (res == NULL)
    {
        fprintf(stderr, "Memory allocation failed when concating string.\n");
        return NULL;
    }

    /* Copy args to resulting string */
    strcpy(res, first);
    va_start(args, first);
    while ((str = va_arg(args, const char*)) != NULL) 
    {
        strcat(res, str);
    }
    va_end(args);

    return res;
}


char* unix_timestamp() 
{
    /* allocate memory for timestamp */
    char *buff = (char *)malloc(TIMESTAMP_LENGTH);
    if (buff == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }


    /* obtain curren time */
    time_t curr_time = time(NULL);
    if (curr_time == (time_t)-1) 
    {
        fprintf(stderr, "Failure to obtain current time.\n");
        free(buff);
        return NULL;
    }

    /* convert current time to str */
    int written = snprintf(buff, TIMESTAMP_LENGTH, "%ld", curr_time);
    if (written < 0 || written >= TIMESTAMP_LENGTH)
    {
        fprintf(stderr, "Timestamp buffer too small or formatting error.\n");
        free(buff);
        return NULL;
    }

    return buff;
}

void timeout(int seconds) 
{
    #ifdef _WIN32
        Sleep(seconds * 1000); // Windows takes ms
    #else
        sleep(seconds);
    #endif
}

void total_path(char* buff, size_t size)
{
    #ifdef _WIN32
        if (GetModuleFileName(NULL, buff, size) == 0)
        {
            fprintf(stderr, "Failed to get executable path.\n");
            exit(EXIT_FAILURE);
        }
    #else
         char temp_path[PATH_MAX];
        if (realpath("/proc/self/exe", temp_path) == NULL) {
            fprintf(stderr, "Failed to get executable path.\n");
            exit(EXIT_FAILURE);
        }
        // Ensure the buffer size is not exceeded
        if (strlen(temp_path) >= size) {
            fprintf(stderr, "Buffer size is too small for the executable path.\n");
            exit(EXIT_FAILURE);
        }
        strncpy(buff, temp_path, size - 1);
        buff[size - 1] = '\0';
    #endif
}