# compile executed when no arguments are given to make.
.PHONY : build


####
#VARIABLES
####
TARGET = client #name of the executable
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
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Specify the C++ compiler and flags
CXX = g++
CXXFLAGS = -std=c++11
CXXFLAGS += -I../dependencies/glm/include/ #add glm path
CXXFLAGS += -I../engine

#Debug
CXXFLAGS_DEBUG = $(CXXFLAGS) -g #-g = debugging symbols
LDFLAGS_DEBUG = -L../engine/bin/Debug/ -lengine
OUT_DEBUG = $(OUTDIR_DEBUG)/$(TARGET)
OBJ_FILES_DEBUG = $(patsubst $(SRC_DIR)/%.cpp,$(OBJDIR_DEBUG)/%.o,$(SRC_FILES))

#Release
CXXFLAGS_RELEASE = $(CXXFLAGS) -O2 #optimization level 2 of 3
LDFLAGS_RELEASE = -L../engine/bin/Release/ -lengine -s
OUT_RELEASE = $(OUTDIR_RELEASE)/$(TARGET)
OBJ_FILES_RELEASE = $(patsubst $(SRC_DIR)/%.cpp,$(OBJDIR_RELEASE)/%.o,$(SRC_FILES))

####
#TARGETS
####

#GENERAL

build: compile_debug compile_release
clean: clean_debug clean_release

#Debug
#create .o file
$(OBJDIR_DEBUG)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $(CXXFLAGS_DEBUG) -o $@ $(LDFLAGS_DEBUG)  $<

before_debug: 
	test -d $(OUTDIR_DEBUG) || mkdir -p $(OUTDIR_DEBUG)
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)	
	test -d $(COPY_DIR_DEBUG) || mkdir -p $(COPY_DIR_DEBUG)

out_debug: $(OBJ_FILES_DEBUG)
	$(CXX) $(CXXFLAGS_DEBUG) -o  $(OUT_DEBUG) $^ $(LDFLAGS_DEBUG)
	cp $(OUTDIR_DEBUG)/$(TARGET) $(COPY_DIR_DEBUG)/ #copy result to destination folder

compile_debug: before_debug out_debug
	
clean_debug: 
	rm -f $(COPY_DIR_DEBUG)/$(TARGET)
	rm -f $(OUT_DEBUG) $(OBJDIR_DEBUG)/*.o
	rm -rf $(OUTDIR_DEBUG)
	rm -rf $(OBJDIR_DEBUG)
	
#Release
#create .o file
$(OBJDIR_RELEASE)/%.o: $(SRC_DIR)/%.cpp
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
	
test:
	echo 'no test implemented'
