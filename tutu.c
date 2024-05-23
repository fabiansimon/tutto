#include <stdio.h>

#include "utils.h"
#include "tutu.h"
#include "logger.h"

void take_snap(const char* snap_dir) 
{
    print_info("Updating Snapshot...");
    
    char *timestamp = unix_timestamp();
    char *snap_file_path = concat_strs(snap_dir, "/", timestamp, NULL);
    printf("Hello World");
    run_command_file("git diff", snap_file_path);
}