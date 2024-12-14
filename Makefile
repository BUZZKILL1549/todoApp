# Compiler selection
CXX := g++

# Compiler flags
CXXFLAGS := -Wall -Wextra -std=c++17 -O2 -Iheaders  # Include the headers directory

# Linking flags
LDFLAGS := -lsqlite3  # Link the SQLite3 library

# Source files and output executables
SOURCES := $(wildcard *.cpp) headers/dbLinker.cpp # Include all .cpp files in the current directory
OBJECTS := $(SOURCES:.cpp=.o)
TARGET := todo  # Output binary named todo (as indicated by your main file)

# Default rule
all: $(TARGET)

# Linking final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Clean up build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all clean
