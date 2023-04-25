CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -Wpedantic -O3 -g

SRC=ECTextViewImp.cpp ECCommand.cpp ECControl.cpp ECEditorTest.cpp
OBJ=$(SRC:.cpp=.o)

TARGET=editor

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean