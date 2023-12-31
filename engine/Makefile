# compile executed when no arguments are given to make.
.PHONY : build

####
#VARIABLES
####

TARGET = libengine.so #name of the .so
TARGET_STATIC = libengine.a #name of the .so
SRC_DIR = src
COPY_DIR_DEBUG = ../Debug
COPY_DIR_RELEASE = ../Release

#Debug
OBJDIR_DEBUG = obj/Debug/src
OUTDIR_DEBUG = bin/Debug

#Release
OBJDIR_RELEASE = obj/Release/src
OUTDIR_RELEASE = bin/Release


####
#SETTINGS
####

#files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_SOURCES = $(wildcard $(TEST_FOLDER)/*_test.cpp)

# Specify the C++ compiler and flags
CXX = g++
CXXFLAGS = -c -fPIC -std=c++11
CXXFLAGS += -I../dependencies/glm/include/ -I../dependencies/freeimage/include/ #add glm and freeimage path
LDFLAGS = -shared
LIB = -lglut -lGL -lGLU -lfreeimage


#Debug
CXXFLAGS_DEBUG = $(CXXFLAGS) -g #-g = debugging symbols
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OUT_DEBUG = $(OUTDIR_DEBUG)/$(TARGET)
OBJ_FILES_DEBUG = $(patsubst $(SRC_DIR)/%.cpp,$(OBJDIR_DEBUG)/%.o,$(SRC_FILES))

#Release
CXXFLAGS_RELEASE = $(CXXFLAGS) -O2 #optimization level 2 of 3
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OUT_RELEASE = $(OUTDIR_RELEASE)/$(TARGET)
OBJ_FILES_RELEASE = $(patsubst $(SRC_DIR)/%.cpp,$(OBJDIR_RELEASE)/%.o,$(SRC_FILES))

####
#TARGETS
####

#GENERAL

build: compile_debug compile_release
clean: clean_debug clean_release

	
#DEBUG

#create .o file
$(OBJDIR_DEBUG)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS_DEBUG) -o $@ $<

before_debug: 
	test -d $(OUTDIR_DEBUG) || mkdir -p $(OUTDIR_DEBUG)
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)
	test -d $(COPY_DIR_DEBUG) || mkdir -p $(COPY_DIR_DEBUG)
	
out_debug: $(OBJ_FILES_DEBUG)
	$(CXX) -fPIC $(LDFLAGS_DEBUG) -o  $(OUT_DEBUG) $^ $(LIB_DEBUG)
	cp $(OUTDIR_DEBUG)/$(TARGET) $(COPY_DIR_DEBUG)/ #copy result to destination folder

out_debug_static: $(OBJ_FILES_DEBUG)
	ar rcs -o $(OUTDIR_DEBUG)/$(TARGET_STATIC) $^
	cp $(OUTDIR_DEBUG)/$(TARGET_STATIC) $(COPY_DIR_DEBUG)/ #copy result to destination folder

compile_debug: before_debug out_debug out_debug_static
	
clean_debug: 
	rm -f $(COPY_DIR_DEBUG)/$(TARGET)	
	rm -f $(COPY_DIR_DEBUG)/$(TARGET_STATIC)
	rm -f $(OUT_DEBUG) $(OBJDIR_DEBUG)/*.o
	rm -rf $(OUTDIR_DEBUG)
	rm -rf $(OBJDIR_DEBUG)

#RELEASE

#create .o file
$(OBJDIR_RELEASE)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS_RELEASE) -o $@ $<

before_release: 
	test -d $(OUTDIR_RELEASE) || mkdir -p $(OUTDIR_RELEASE)
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)
	test -d $(COPY_DIR_RELEASE) || mkdir -p $(COPY_DIR_RELEASE)
	
out_release: $(OBJ_FILES_RELEASE)
	$(CXX) -fPIC $(LDFLAGS_RELEASE) -o  $(OUT_RELEASE) $^ $(LIB_RELEASE)
	cp $(OUTDIR_RELEASE)/$(TARGET) $(COPY_DIR_RELEASE)/  #copy result to destination folder
	
	
out_release_static: $(OBJ_FILES_RELEASE)
	ar rcs -o $(OUTDIR_RELEASE)/$(TARGET_STATIC) $^
	cp $(OUTDIR_RELEASE)/$(TARGET_STATIC) $(COPY_DIR_RELEASE)/ #copy result to destination folder
	
compile_release: before_release out_release out_release_static
	
clean_release: 
	rm -f $(COPY_DIR_RELEASE)/$(TARGET)
	rm -f $(COPY_DIR_RELEASE)/$(TARGET_STATIC)
	rm -f $(OUT_RELEASE) $(OBJDIR_RELEASE)/*.o
	rm -rf $(OUTDIR_RELEASE)
	rm -rf $(OBJDIR_RELEASE)

test:
	cd ../engine_test && make test
