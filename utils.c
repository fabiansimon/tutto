#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

#include <mach-o/dyld.h>
#include <unistd.h>
#include <limits.h>

#include "utils.h"
#include "macros.h"

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
    /* Cross Platform implementation needed */
    sleep(seconds);
}

void run_command(const char* cmd) 
{
    system(cmd);
}

int binary_input(char* input, size_t size, char* expected)
{
    if (fgets(input, size, stdin) != NULL)
    {
        input[strcspn(input, "\n")] = 0;
        if (strcasecmp(input, expected) == 0)
        {
            return 1;
        }
    }

    return 0;
}