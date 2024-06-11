# Compiler
CXX = g++

# Directories
LIB_DIR = /Users/daghanerdonmez/SFML/build/lib

# Libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Compiler flags
CXXFLAGS = -I$(LIB_DIR) -Wl,-rpath,$(LIB_DIR)

# Source files
SRCS = main.cpp Ball.cpp MyMath.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = prog

# Default rule
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) -L$(LIB_DIR) $(LIBS) $(CXXFLAGS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) -c $< -o $@

# Rule to clean the build directory
clean:
	rm -f $(OBJS) $(TARGET)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run


#main command was
#g++ main.cpp Ball.cpp -o prog -L/Users/daghanerdonmez/SFML/build/lib -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,/Users/daghanerdonmez/SFML/build/lib
#this