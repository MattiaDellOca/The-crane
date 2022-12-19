# Default target executed when no arguments are given to make.
#default_target: compile
.PHONY : compile

# Specify the target executable
TARGET = libengine.so #name of the .so

#general 
SRC_DIR = src
#OBJ_DIR = obj2
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
#OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

#test files
TEST_SOURCES = $(wildcard $(TEST_FOLDER)/*_test.cpp)

# Specify the C++ compiler and flags
CXX = g++
CXXFLAGS = -c -fPIC -std=c++11 -Wall -Wextra 
CXXFLAGS += -I../dependencies/glm/include/ #add glm path
LDFLAGS = -shared
LIB = -lglut -lGL


#Debug
CXXFLAGS_DEBUG = $(CXXFLAGS) -g #-g = debugging symbols
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug/src
OUTDIR_DEBUG = bin/Debug
OUT_DEBUG = $(OUTDIR_DEBUG)/$(TARGET)
OBJ_FILES_DEBUG = $(patsubst $(SRC_DIR)/%.cpp,$(OBJDIR_DEBUG)/%.o,$(SRC_FILES))

#Release
CXXFLAGS_RELEASE = $(CXXFLAGS) -02 #optimization level 2 of 3
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release/src
OUTDIR_RELEASE = bin/Release
OUT_RELEASE = $(OUTDIR_RELEASE)/$(TARGET)
OBJ_FILES_RELEASE = $(patsubst $(SRC_DIR)/%.cpp,$(OBJDIR_RELEASE)/%.o,$(SRC_FILES))

####
#TARGETS
####

#GENERAL

compile: compile_debug compile_release
clean: clean_debug clean_release

	
#DEBUG

#create .o file
$(OBJDIR_DEBUG)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

before_debug: 
	test -d $(OUTDIR_DEBUG) || mkdir -p $(OUTDIR_DEBUG)
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

out_debug: $(OBJ_FILES_DEBUG)
	$(CXX) -fPIC $(LDFLAGS_DEBUG) -o  $(OUT_DEBUG) $^ $(LIB_DEBUG)

compile_debug: before_debug out_debug
	
clean_debug: 
	rm -f $(OUT_DEBUG) $(OBJDIR_DEBUG)/*.o
	rm -rf $(OUTDIR_DEBUG)
	rm -rf $(OBJDIR_DEBUG)

#RELEASE

#create .o file
$(OBJDIR_RELEASE)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

before_release: 
	test -d $(OUTDIR_RELEASE) || mkdir -p $(OUTDIR_RELEASE)
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

out_release: $(OBJ_FILES_RELEASE)
	$(CXX) -fPIC $(LDFLAGS_RELEASE) -o  $(OUT_RELEASE) $^ $(LIB_RELEASE)

compile_release: before_release out_release
	
clean_release: 
	rm -f $(OUT_RELEASE) $(OBJDIR_RELEASE)/*.o
	rm -rf $(OUTDIR_RELEASE)
	rm -rf $(OBJDIR_RELEASE)




#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
#	$(CXX) $(CXXFLAGS) -o $@ $<
# Compile the source files into the target executable
#compile: $(OBJ_FILES)
#	$(CXX) -fPIC $(LDFLAGS) -o  $(TARGET) $^ $(LIB)

# Compile the test files into the test executable
#compile_test: $(TEST_SOURCES) compile
#	$(CXX) $(CXXFLAGS) $(GTEST_FLAGS) -o $(TEST_TARGET) $(TEST_SOURCES) $(GTEST_LIBS)

#Run the test executable
#test: compile_test
#	./$(TEST_TARGET)

# Clean up object files and executables
#clean:
#	rm -f $(TARGET) $(TEST_TARGET) $(OBJ_DIR)/*.o
	
	

