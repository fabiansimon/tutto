#ifndef MACROS_H
#define MACROS_H

#define CONCATENATE(a, b) a b

/* Naming Macros */
#define PROJECT_NAME "Tutu"
#define PROJECT_ENDING "tutu"

#define TIMESTAMP_LENGTH 20

/* Config Macros */
#define CONFIG_LINE_BUFFER_SIZE 256
#define CONFIG_PATH "config." PROJECT_ENDING
#define CONFIG_INIT_CONTENT \
    "# Simple TUTU config file\n" \
    "INTERVAL_SECONDS=10\n" \
    "PROJECT_NAME=Project Example\n" 

/* Color Macros */
#define RED_TEXT "\x1b[31m"
#define GREEN_TEXT "\x1b[32m"
#define BLUE_TEXT "\x1b[34m"
#define RESET_TEXT "\x1b[0m"

#endif