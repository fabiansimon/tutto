#ifndef MACROS_H
#define MACROS_H

/* Randos */
#define CONCATENATE(a, b) a b
#define TIMESTAMP_LENGTH 20
#define GIT_DIFF_BUFFER_SIZE 65536

/* Naming Macros */
#define PROJECT_NAME "Tutu"
#define PROJECT_ENDING "tutu"


/* Config Macros */
#define CONFIG_LINE_BUFFER_SIZE 256
#define CONFIG_PATH "config." PROJECT_ENDING
#define CONFIG_INIT_CONTENT \
    "# Simple TUTU config file\n" \
    "INTERVAL_SECONDS=60\n" \
    "PROJECT_NAME=Project Example\n" 

/* Snapshot hidden directoy */
#define SNAP_DIRECTORY_NAME ".tutu_snap"
#define SNAP_DIRECTORY_MODE 0755

/* Color Macros */
#define RED_TEXT "\x1b[31m"
#define GREEN_TEXT "\x1b[32m"
#define BLUE_TEXT "\x1b[34m"
#define RESET_TEXT "\x1b[0m"

#endif
