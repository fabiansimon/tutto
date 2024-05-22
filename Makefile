# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Target executable
TARGET = main

# Source files
SRCS = main.c config.c utils.c dir.c logger.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HDRS = config.h utils.h macros.h dir.h logger.h

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile source files into object files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
