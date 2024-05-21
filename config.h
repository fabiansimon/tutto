#ifndef CONFIG_H
#define CONFIG_H


#define CONFIG_LINE_BUFFER_SIZE 256

typedef struct {
    char project_name[CONFIG_LINE_BUFFER_SIZE/2];
    int interval_mins;
} Config;

int read_config(const char *filename, Config *config);

#endif