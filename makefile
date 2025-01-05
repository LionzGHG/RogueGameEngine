# Compiler and flags
CC = gcc
CFLAGS = -Wall
LDFLAGS = -lgdi32

# Source files
SRCS = main.c window.c render.c core.c traits.c math.c fs.c assets.c

# Object files (derived from source files)
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = rogue.exe

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	del /q $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean