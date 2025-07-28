CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -Wpedantic -O2 -g -I../TextViewImpCode

# Source files from the main project
SRC_DIR=../TextViewImpCode
SRC_FILES=$(SRC_DIR)/ECModel.cpp $(SRC_DIR)/ECController.cpp $(SRC_DIR)/ECCommand.cpp $(SRC_DIR)/ECTextViewImp.cpp

# Test files
TEST_FILES=SimpleTest.cpp ConstantsTest.cpp LogicTest.cpp

# Test executables  
TESTS=SimpleTest ConstantsTest LogicTest

.PHONY: all clean test run-tests

all: $(TESTS)

SimpleTest: SimpleTest.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

ConstantsTest: ConstantsTest.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

LogicTest: LogicTest.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

test: $(TESTS)
	@echo "Running all tests..."
	@for test in $(TESTS); do \
		echo ""; \
		echo "=== Running $$test ==="; \
		./$$test || exit 1; \
	done
	@echo ""
	@echo "All tests passed!"

run-tests: test

clean:
	rm -f $(TESTS)
	rm -f *.o

# Individual test targets
test-simple: SimpleTest
	./SimpleTest

test-constants: ConstantsTest
	./ConstantsTest

test-logic: LogicTest
	./LogicTest

help:
	@echo "Available targets:"
	@echo "  all           - Build all tests"
	@echo "  test          - Build and run all tests"
	@echo "  run-tests     - Alias for test"
	@echo "  clean         - Remove test executables"
	@echo "  test-simple   - Run simple framework tests"
	@echo "  test-constants - Run constants and enums tests"
	@echo "  test-logic    - Run pure logic tests"
	@echo "  help          - Show this help"