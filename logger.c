#include <stdio.h>

#include "macros.h"
#include "logger.h"

void print_error(const char* msg)
{
    printf(RED_TEXT "ERROR: \t%s\n" RESET_TEXT, msg);
}

void print_info(const char* msg)
{
    printf(BLUE_TEXT "INFO: \t%s\n" RESET_TEXT, msg);
}

void print_success(const char* msg)
{
    printf(GREEN_TEXT "SUCCESS: \t%s\n" RESET_TEXT, msg);
}