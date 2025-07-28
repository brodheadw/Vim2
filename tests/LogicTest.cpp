//
// Logic Tests - Test pure logic and algorithms
// Created by Claude Code
//

#include "TestFramework.h"
#include "../TextViewImpCode/ECTextViewImp.h"
#include <string>
#include <vector>

// Test string manipulation logic that might be used in the editor
TEST(StringLogic_BasicOperations) {
    std::string text = "Hello World";
    
    // Test string insertion at position
    std::string result = text;
    result.insert(6, "Big ");
    ASSERT_STR_EQ("Hello Big World", result);
    
    // Test string removal
    result = text;
    result.erase(5, 1); // Remove space
    ASSERT_STR_EQ("HelloWorld", result);
    
    // Test substring extraction
    std::string sub = text.substr(6, 5); // Extract "World"
    ASSERT_STR_EQ("World", sub);
}

// Test cursor position calculations
TEST(CursorLogic_PositionCalculations) {
    // Test cursor movement bounds checking logic
    int cursorX = 5;
    int lineLength = 10;
    
    // Move right within bounds
    if (cursorX < lineLength) {
        cursorX++;
    }
    ASSERT_EQ(6, cursorX);
    
    // Move right at boundary (should not move beyond)
    cursorX = lineLength;
    int originalX = cursorX;
    if (cursorX < lineLength) {
        cursorX++;
    }
    ASSERT_EQ(originalX, cursorX); // Should not change
    
    // Move left within bounds
    cursorX = 3;
    if (cursorX > 0) {
        cursorX--;
    }
    ASSERT_EQ(2, cursorX);
    
    // Move left at boundary (should not move beyond)
    cursorX = 0;
    originalX = cursorX;
    if (cursorX > 0) {
        cursorX--;
    }
    ASSERT_EQ(originalX, cursorX); // Should not change
}

// Test line manipulation logic
TEST(LineLogic_Operations) {
    std::vector<std::string> lines = {"First", "Second", "Third"};
    
    // Test line insertion
    lines.insert(lines.begin() + 1, "Inserted");
    ASSERT_EQ(4, static_cast<int>(lines.size()));
    ASSERT_STR_EQ("First", lines[0]);
    ASSERT_STR_EQ("Inserted", lines[1]);
    ASSERT_STR_EQ("Second", lines[2]);
    
    // Test line removal
    lines.erase(lines.begin() + 1);
    ASSERT_EQ(3, static_cast<int>(lines.size()));
    ASSERT_STR_EQ("First", lines[0]);
    ASSERT_STR_EQ("Second", lines[1]);
    ASSERT_STR_EQ("Third", lines[2]);
}

// Test newline splitting logic
TEST(LineLogic_NewlineSplit) {
    std::string line = "Hello World";
    int splitPos = 6;
    
    // Split line at position (simulate Enter key)
    std::string firstPart = line.substr(0, splitPos);
    std::string secondPart = line.substr(splitPos);
    
    ASSERT_STR_EQ("Hello ", firstPart);
    ASSERT_STR_EQ("World", secondPart);
    
    // Test split at beginning
    firstPart = line.substr(0, 0);
    secondPart = line.substr(0);
    
    ASSERT_STR_EQ("", firstPart);
    ASSERT_STR_EQ("Hello World", secondPart);
    
    // Test split at end
    firstPart = line.substr(0, line.length());
    secondPart = line.substr(line.length());
    
    ASSERT_STR_EQ("Hello World", firstPart);
    ASSERT_STR_EQ("", secondPart);
}

// Test character type detection
TEST(CharacterLogic_TypeDetection) {
    // Test printable characters
    ASSERT_TRUE(isprint('A'));
    ASSERT_TRUE(isprint('z'));
    ASSERT_TRUE(isprint('0'));
    ASSERT_TRUE(isprint(' '));
    
    // Test non-printable characters
    ASSERT_FALSE(isprint('\n'));
    ASSERT_FALSE(isprint('\t'));
    ASSERT_FALSE(isprint(0));
    ASSERT_FALSE(isprint(27)); // ESC
    
    // Test alphanumeric
    ASSERT_TRUE(isalnum('A'));
    ASSERT_TRUE(isalnum('9'));
    ASSERT_FALSE(isalnum(' '));
    ASSERT_FALSE(isalnum('!'));
}

// Test bounds checking logic
TEST(BoundsLogic_ArrayAccess) {
    std::vector<std::string> lines = {"Line 1", "Line 2", "Line 3"};
    int row = 1;
    int col = 3;
    
    // Test valid access
    bool validRow = (row >= 0 && row < static_cast<int>(lines.size()));
    ASSERT_TRUE(validRow);
    
    if (validRow) {
        bool validCol = (col >= 0 && col <= static_cast<int>(lines[row].length()));
        ASSERT_TRUE(validCol);
    }
    
    // Test invalid row access
    row = 5;
    validRow = (row >= 0 && row < static_cast<int>(lines.size()));
    ASSERT_FALSE(validRow);
    
    // Test invalid column access
    row = 1;
    col = 100;
    validRow = (row >= 0 && row < static_cast<int>(lines.size()));
    if (validRow) {
        bool validCol = (col >= 0 && col <= static_cast<int>(lines[row].length()));
        ASSERT_FALSE(validCol);
    }
}

// Test mode state logic
TEST(StateLogic_ModeHandling) {
    int mode = 0; // Command mode
    
    // Test mode switching
    ASSERT_EQ(0, mode);
    
    mode = 1; // Edit mode
    ASSERT_EQ(1, mode);
    
    mode = 0; // Back to command mode
    ASSERT_EQ(0, mode);
    
    // Test mode validation
    bool validMode = (mode == 0 || mode == 1);
    ASSERT_TRUE(validMode);
    
    mode = 2; // Invalid mode
    validMode = (mode == 0 || mode == 1);
    ASSERT_FALSE(validMode);
}

RUN_ALL_TESTS()