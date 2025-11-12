
# Use the C++ compiler for linking to pull in the C++ standard library
CXX=c++
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror

SRC=add.cpp main.cpp
TARGET=ex00

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean
