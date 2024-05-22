#ifndef UTILS_H
#define UTILS_H

char *concat_strs(const char *first, ...);
char *unix_timestamp();
void timeout(int seconds);
void run_command(const char *cmd);
void run_command_output(const char *cmd, char *output, size_t size);
void run_command_file(const char *cmd, const char *filename);
int binary_input(char *input, size_t size, char *expected);

#endif