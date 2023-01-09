# compile executed when no arguments are given to make.
.PHONY : build 


####
#VARIABLES
####
TARGET = test #name of the executable

#Debug
#OBJDIR_DEBUG = obj/Debug/src
#OUTDIR_DEBUG = bin/Debug

#Release
OBJDIR_RELEASE = obj/Release
OUTDIR_RELEASE = bin/Release
COPY_DIR_RELEASE = ../Release

####
#SETTINGS
####
TEST_FILES = $(wildcard *_test.cpp) main.cpp pch.cpp
OBJ_FILES = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(TEST_FILES))



# Specify the C++ compiler and flags
CXX = g++
CXXFLAGS = -std=c++14
CXXFLAGS += -I../dependencies/glm/include/ #add glm path
CXXFLAGS += -I../engine
CXXFLAGS += -I../dependencies/googletest/include
#Debug
#CXXFLAGS_DEBUG = $(CXXFLAGS) -g #-g = debugging symbols
#LDFLAGS_DEBUG = -L../engine/bin/Debug/ -lengine
#OUT_DEBUG = $(OUTDIR_DEBUG)/$(TARGET)
#OBJ_FILES_DEBUG = $(patsubst $(SRC_DIR)/%.cpp,$(OBJDIR_DEBUG)/%.o,$(SRC_FILES))

#Release
CXXFLAGS_RELEASE = $(CXXFLAGS) -O2 #optimization level 2 of 3
LDFLAGS_RELEASE = -L../engine/bin/Release/ -lengine -L../dependencies/googletest/lib  -lgtest  -s
OUT_RELEASE = $(OUTDIR_RELEASE)/$(TARGET)
OBJ_FILES_RELEASE = $(patsubst %.cpp,$(OBJDIR_RELEASE)/%.o,$(TEST_FILES))

####
#TARGETS
####

#GENERAL

build: compile_release 
clean: clean_release
test: clean_release compile_release exec_test

#Release
#create .o file
$(OBJDIR_RELEASE)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS_RELEASE) -o $@ $(LDFLAGS_RELEASE) $<

before_release: 
	test -d $(OUTDIR_RELEASE) || mkdir -p $(OUTDIR_RELEASE)
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)
	test -d $(COPY_DIR_RELEASE) || mkdir -p $(COPY_DIR_RELEASE)

out_release: $(OBJ_FILES_RELEASE)
	$(CXX) $(CXXFLAGS_RELEASE) -o  $(OUT_RELEASE) $^ $(LDFLAGS_RELEASE) 
	cp $(OUTDIR_RELEASE)/$(TARGET) $(COPY_DIR_RELEASE)/  #copy result to destination folder

compile_release: before_release out_release
	
clean_release: 
	rm -f $(COPY_DIR_RELEASE)/$(TARGET)
	rm -f $(OUT_RELEASE) $(OBJDIR_RELEASE)/*.o
	rm -rf $(OUTDIR_RELEASE)
	rm -rf $(OBJDIR_RELEASE)
	
exec_test:
	LD_LIBRARY_PATH=:../dependencies/googletest/lib:../engine/bin/Release ./$(OUT_RELEASE)
	
