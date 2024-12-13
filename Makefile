# Compiler selection
CXX := g++

# Compiler flags
CXXFLAGS := -Wall -Wextra -std=c++17 -O2

# Source files and output executables
SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.0)
TARGET := main

# Default rule
all: $(TARGET)

# Linking final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean up build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all clean
