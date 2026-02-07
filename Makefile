# Variables
CXX = g++
CXXFLAGS = -Wall  -Wextra -Werror -std=c++17  -fsanitize=address -g
PROGRAM = computor
SOURCES = main.cpp

all: $(PROGRAM)

# Build the program
$(PROGRAM): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(SOURCES)

# Clean up temporary files
clean:
	rm -f $(PROGRAM) *.o