
# Use the C++ compiler for linking to pull in the C++ standard library
CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror -g -O0
INC := -I ./inc
AR := ar
ARFLAGS := rcs

SRC_DIR := src
INC_DIR := inc
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
LIB_DIR := $(BUILD_DIR)/lib
BIN_DIR := $(BUILD_DIR)/bin

LIB_NAME := librsb.a
LIB_PATH := $(LIB_DIR)/$(LIB_NAME)

# list exercises by folder name under exercises/
EXERCISES := ex00 ex01 ex02 ex03 ex04 #ex05 ex06 ex07 ex08 ex09 ex10 ex11

# derived lists
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

EXE_DIRS := $(addprefix exercises/,$(EXERCISES))
# Build binary paths by prefixing the bin dir to exercise names
EXES := $(addprefix $(BIN_DIR)/,$(EXERCISES))

all: dirs $(LIB_PATH) exercises Makefile
	@echo "Build complete. Binaries in $(BIN_DIR)."

# create build dirs
dirs:
	@mkdir -p $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR)

# build object files for library
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

# archive into static library
$(LIB_PATH): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^
	@echo "Built $(LIB_PATH)"

# build all exercises
exercises: $(EXES)

# each exercise executable depends on its main.cpp and the static lib
# pattern: exercises/ex00 -> binary at build/bin/ex00
$(BIN_DIR)/%: exercises/%/main.cpp $(LIB_PATH)
	$(CXX) $(CXXFLAGS) $< $(LIB_PATH) -o $@
	@echo "Built $@"

# convenience targets to build single exercise, e.g. `make ex=ex01`
# or `make ex=ex00`
ifeq ($(ex),)
# nothing
else
single: dirs $(LIB_PATH) $(BIN_DIR)/$(ex)
	@echo "Built single exercise: $(ex)"
endif

clean:
	@rm -rf $(BUILD_DIR)
	@echo "Cleaned build artifacts."

# distclean: clean
# # add here if you generate other artifacts
# 	@echo "Distclean done."

.PHONY: all lib clean dirs exercises $(EXERCISES) single #distclean 

