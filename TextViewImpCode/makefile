CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -Wpedantic -O3 -g

SRC=ECTextViewImp.cpp ECCommand.cpp ECControl.cpp ECEditorTest.cpp
OBJ=$(SRC:.cpp=.o)

TARGET=editor

.PHONY: all build_and_clean clean

all: build_and_clean

build_and_clean: $(TARGET) clean

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

# clean only files with .o extension:
clean:
	rm -f *.o