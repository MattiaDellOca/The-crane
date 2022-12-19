# Default target executed when no arguments are given to make.
default_target: compile
.PHONY : default_target

# Specify the target executable
TARGET = client #name of the executable

#the source files
SRC_DIR = src
OBJ_DIR = obj2
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Specify the C++ compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra 
CXXFLAGS += -I../dependencies/glm/include/ #add glm path
CXXFLAGS += -I../graphicsEngine

LDFLAGS += -L../graphicsEngine/ -lengine

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
	$(CXX) -c $(CXXFLAGS) -o $@ $(LDFLAGS) $<
	
# Compile the source files into the target executable
compile: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $^ $(LDFLAGS)

# Clean up object files and executables
clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJ_DIR)/*.o
	
	

