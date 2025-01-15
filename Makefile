# Makefile for TaskMaster C++
# Author: Shreenidhi V

# Compiler and flags
# Using g++ with C++17 standard and enabling common warnings for better code quality.
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# The name of the final executable file.
TARGET = taskmaster

# The single source file for the project.
SRCS = task.cpp

# Object file, derived automatically from the source file name.
OBJS = $(SRCS:.cpp=.o)

# Default target: builds the executable. This is the rule that runs when you just type `make`.
all: $(TARGET)

# Rule to link the object file(s) into the final executable.
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile a .cpp source file into a .o object file.
# The `$<` variable refers to the first prerequisite (the .cpp file).
# The `$@` variable refers to the target (the .o file).
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up the directory.
# Removes the executable and any generated object files.
clean:
	rm -f $(TARGET) $(OBJS) tasks.json

# Phony targets are not actual files. They are used for commands that don't produce a file with the same name.
.PHONY: all clean