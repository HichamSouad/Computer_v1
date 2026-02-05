# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++17
PROGRAM = computor
SOURCES = main.cpp

# Default target
all: $(PROGRAM)

# Build the program
$(PROGRAM): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(SOURCES)

# Clean up temporary files
clean:
	rm -f $(PROGRAM) *.o