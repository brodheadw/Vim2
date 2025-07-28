//
// Simple Test - Just test that code compiles and basic logic works
// Created by Claude Code
//

#include "TestFramework.h"
#include "../TextViewImpCode/ECTextViewImp.h"

// Test basic arithmetic to verify test framework works
TEST(Basic_Arithmetic) {
    ASSERT_EQ(2, 1 + 1);
    ASSERT_EQ(4, 2 * 2);
    ASSERT_EQ(0, 5 - 5);
}

TEST(Basic_StringComparison) {
    std::string hello = "Hello";
    std::string world = "World";
    
    ASSERT_STR_EQ("Hello", hello);
    ASSERT_TRUE(hello != world);
    ASSERT_FALSE(hello == world);
}

TEST(Basic_BooleanLogic) {
    ASSERT_TRUE(true);
    ASSERT_FALSE(false);
    ASSERT_TRUE(1 == 1);
    ASSERT_FALSE(1 == 2);
}

// Test enums from ECTextViewImp.h
TEST(KeyConstants_Exist) {
    // Test that key constants are defined
    int arrowLeft = ARROW_LEFT;
    int arrowRight = ARROW_RIGHT;
    int ctrlZ = CTRL_Z;
    int ctrlQ = CTRL_Q;
    
    ASSERT_TRUE(arrowLeft > 0);
    ASSERT_TRUE(arrowRight > 0);
    ASSERT_TRUE(ctrlZ > 0);
    ASSERT_TRUE(ctrlQ > 0);
}

TEST(TextColors_Exist) {
    // Test that color constants are defined
    int red = TEXT_COLOR_RED;
    int green = TEXT_COLOR_GREEN;
    int blue = TEXT_COLOR_BLUE;
    
    ASSERT_TRUE(red > 0);
    ASSERT_TRUE(green > 0);
    ASSERT_TRUE(blue > 0);
}

RUN_ALL_TESTS()