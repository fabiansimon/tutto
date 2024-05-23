# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Target executable
TARGET = main

# Source files
SRCS = main.c config.c utils.c dir.c logger.c tutu.c

# Object files directory
OBJDIR = obj

# Object files
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# Header files
HDRS = config.h utils.h macros.h dir.h logger.h tutu.h

# Default target
all: $(TARGET)

# Create the object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Link the object files to create the executable
$(TARGET): $(OBJDIR) $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile source files into object files
$(OBJDIR)/%.o: %.c $(HDRS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Phony targets
.PHONY: all clean
