//
// Constants and Enums Tests
// Created by Claude Code
//

#include "TestFramework.h"
#include "../TextViewImpCode/ECTextViewImp.h"

// Test that key action constants are properly defined
TEST(KeyActions_ArrowKeys) {
    ASSERT_TRUE(ARROW_LEFT > 0);
    ASSERT_TRUE(ARROW_RIGHT > 0);
    ASSERT_TRUE(ARROW_UP > 0);
    ASSERT_TRUE(ARROW_DOWN > 0);
    
    // Arrow keys should have different values
    ASSERT_TRUE(ARROW_LEFT != ARROW_RIGHT);
    ASSERT_TRUE(ARROW_UP != ARROW_DOWN);
}

TEST(KeyActions_ControlKeys) {
    ASSERT_TRUE(CTRL_A > 0);
    ASSERT_TRUE(CTRL_Q > 0);
    ASSERT_TRUE(CTRL_S > 0);
    ASSERT_TRUE(CTRL_Z > 0);
    ASSERT_TRUE(CTRL_Y > 0);
    
    // Control keys should be in expected range (1-26)
    ASSERT_TRUE(CTRL_A >= 1 && CTRL_A <= 26);
    ASSERT_TRUE(CTRL_Z >= 1 && CTRL_Z <= 26);
}

TEST(KeyActions_SpecialKeys) {
    ASSERT_EQ(27, ESC);      // ESC should be ASCII 27
    ASSERT_EQ(13, ENTER);    // Enter should be ASCII 13
    ASSERT_EQ(9, TAB);       // Tab should be ASCII 9
    ASSERT_EQ(127, BACKSPACE); // Backspace should be ASCII 127
}

TEST(KeyActions_VirtualKeys) {
    // Virtual keys should be >= 1000 (as per comment in header)
    ASSERT_TRUE(ARROW_LEFT >= 1000);
    ASSERT_TRUE(ARROW_RIGHT >= 1000);
    ASSERT_TRUE(ARROW_UP >= 1000);
    ASSERT_TRUE(ARROW_DOWN >= 1000);
    ASSERT_TRUE(DEL_KEY >= 1000);
    ASSERT_TRUE(HOME_KEY >= 1000);
    ASSERT_TRUE(END_KEY >= 1000);
    ASSERT_TRUE(PAGE_UP >= 1000);
    ASSERT_TRUE(PAGE_DOWN >= 1000);
}

// Test text color constants
TEST(TextColors_BasicColors) {
    ASSERT_EQ(30, TEXT_COLOR_BLACK);
    ASSERT_EQ(31, TEXT_COLOR_RED);
    ASSERT_EQ(32, TEXT_COLOR_GREEN);
    ASSERT_EQ(33, TEXT_COLOR_YELLOW);
    ASSERT_EQ(34, TEXT_COLOR_BLUE);
    ASSERT_EQ(35, TEXT_COLOR_MAGENTA);
    ASSERT_EQ(36, TEXT_COLOR_CYAN);
    ASSERT_EQ(37, TEXT_COLOR_WHITE);
    ASSERT_EQ(-1, TEXT_COLOR_DEF);
}

TEST(TextColors_AllDifferent) {
    // All colors should have different values (except default)
    int colors[] = {
        TEXT_COLOR_BLACK, TEXT_COLOR_RED, TEXT_COLOR_GREEN,
        TEXT_COLOR_YELLOW, TEXT_COLOR_BLUE, TEXT_COLOR_MAGENTA,
        TEXT_COLOR_CYAN, TEXT_COLOR_WHITE
    };
    
    int numColors = sizeof(colors) / sizeof(colors[0]);
    
    // Check that all colors are different
    for (int i = 0; i < numColors; i++) {
        for (int j = i + 1; j < numColors; j++) {
            ASSERT_TRUE(colors[i] != colors[j]);
        }
    }
}

// Test logical relationships between constants
TEST(KeyActions_LogicalRelationships) {
    // Arrow keys should be sequential
    ASSERT_EQ(ARROW_RIGHT, ARROW_LEFT + 1);
    ASSERT_EQ(ARROW_UP, ARROW_RIGHT + 1);
    ASSERT_EQ(ARROW_DOWN, ARROW_UP + 1);
}

// Test that constants are within reasonable ranges
TEST(Constants_Ranges) {
    // ASCII printable characters should be 32-126
    ASSERT_TRUE(' ' == 32);  // Space
    ASSERT_TRUE('A' >= 65 && 'A' <= 90);   // Uppercase
    ASSERT_TRUE('a' >= 97 && 'a' <= 122);  // Lowercase
    ASSERT_TRUE('0' >= 48 && '0' <= 57);   // Digits
    
    // Special keys should be outside printable range
    ASSERT_TRUE(ARROW_LEFT > 126);
    ASSERT_TRUE(CTRL_A < 32);
}

RUN_ALL_TESTS()