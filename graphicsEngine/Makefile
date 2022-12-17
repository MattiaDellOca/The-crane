# Specify the target executable and the source files
TARGET = myprogram
SOURCES = $(wildcard *.cpp)

# Specify the C++ compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Specify the unit testing library and flags
GTEST_DIR = /path/to/gtest
GTEST_FLAGS = -isystem $(GTEST_DIR)/include
GTEST_LIBS = -L$(GTEST_DIR) -lgtest -lgtest_main

# Specify the test executable and the test files
TEST_TARGET = test
TEST_SOURCES = $(wildcard *_test.cpp)

# Compile the source files into the target executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Compile the test files into the test executable
$(TEST_TARGET): $(TEST_SOURCES) $(TARGET)
	$(CXX) $(CXXFLAGS) $(GTEST_FLAGS) -o $(TEST_TARGET) $(TEST_SOURCES) $(GTEST_LIBS)

# Run the test executable
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean up object files and executables
clean:
	rm -f $(TARGET) $(TEST_TARGET)