#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

#include <mach-o/dyld.h>
#include <unistd.h>
#include <limits.h>

#include "utils.h"
#include "logger.h"
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

void run_command_output(const char *cmd, char *output, size_t size)
{
    FILE *pipe = popen(cmd, "r");
    if (pipe == NULL)
    {
        perror("Error while creating pipe.");
        exit(0);
    }

    char buff[128];
    size_t curr_length = 0;

    output[0] = '\0';

    while (fgets(buff, sizeof(buff), pipe) != NULL)
    {
        size_t buff_length = strlen(buff);

        if (curr_length + buff_length >= size -1)
        {
            //fprintf(stderr, "Output buffer is too small");
            break;
        }

        strcat(output, buff);
        curr_length += buff_length;
    }

    int status = pclose(pipe);
    if (status == -1)
    {
        perror("Error while closing pipe.");
        exit(0);
    }
}

void run_command_file(const char* cmd, const char* filename)
{
    char buffer[128];
    run_command_output(cmd, buffer, sizeof(buffer));

    if (buffer[0] == '\0') {
        print_info("No changes detected.");
        return;
    }

    // Clean buffer to reuse for file
    memset(buffer, 0, sizeof(buffer));

    FILE *pipe = popen(cmd, "r");
    if (pipe == NULL)
    {
        perror("Error while creating pipe.");
        exit(0);
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Error while opening file");
        pclose(pipe);
        exit(0);
    }

    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        fprintf(file, "%s", buffer);
    }

    int status = pclose(pipe);
    if (status == -1)
    {
        perror("Error while closing pipe.");
        exit(0);
    }

    if (fclose(file) != 0)
    {
        perror("Error while closing file.");
        exit(0);
    }
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