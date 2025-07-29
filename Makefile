# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra

# Output binary name
TARGET = compiler

# Source files and object files
SRCS = src/main.cpp libpx/lexer.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)


# Default target: build the program
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

