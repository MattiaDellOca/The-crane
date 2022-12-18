# Default target executed when no arguments are given to make.
default_target: compile
.PHONY : default_target

# Specify the target executable
TARGET = libengine.so #name of the .so

#the source files
SRC_DIR = src
OBJ_DIR = obj2
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Specify the C++ compiler and flags
CXX = g++
CXXFLAGS = -c -fPIC -std=c++11 -Wall -Wextra 
CXXFLAGS += -I../dependencies/glm/include/ #add glm path
LDFLAGS = -shared
LIB = -lglut -lGL


# Specify the unit testing library and flags
#GTEST_DIR = /googletest-release-1.12.1
#GTEST_FLAGS = -isystem $(GTEST_DIR)/include
#GTEST_LIBS = -L$(GTEST_DIR) -lgtest -lgtest_main

# Specify the test executable and the test files
TEST_TARGET = testFile #name of the test file
TEST_FOLDER = test
TEST_SOURCES = $(wildcard $(TEST_FOLDER)/*_test.cpp)

#create .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<


# Compile the source files into the target executable
compile: $(OBJ_FILES)
	$(CXX) $(LDFLAGS) -o  $(TARGET) $^ $(LIB)

# Compile the test files into the test executable
compile_test: $(TEST_SOURCES) compile
	$(CXX) $(CXXFLAGS) $(GTEST_FLAGS) -o $(TEST_TARGET) $(TEST_SOURCES) $(GTEST_LIBS)

#Run the test executable
test: compile_test
	./$(TEST_TARGET)

# Clean up object files and executables
clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJ_DIR)/*.o
	
	

