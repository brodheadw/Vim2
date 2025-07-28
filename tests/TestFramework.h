//
// Simple Test Framework for Vim2 Editor
// Created by Claude Code
//

#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>

class TestFramework {
public:
    static TestFramework& getInstance() {
        static TestFramework instance;
        return instance;
    }
    
    void addTest(const std::string& name, std::function<void()> test) {
        tests.push_back({name, test});
    }
    
    void runAllTests() {
        std::cout << "Running " << tests.size() << " tests...\n" << std::endl;
        
        int passed = 0;
        int failed = 0;
        
        for (const auto& test : tests) {
            std::cout << "Running: " << test.name << " ... ";
            try {
                test.func();
                std::cout << "PASSED" << std::endl;
                passed++;
            } catch (const std::exception& e) {
                std::cout << "FAILED: " << e.what() << std::endl;
                failed++;
            }
        }
        
        std::cout << "\nResults: " << passed << " passed, " << failed << " failed" << std::endl;
        
        if (failed > 0) {
            exit(1);
        }
    }
    
private:
    struct Test {
        std::string name;
        std::function<void()> func;
    };
    
    std::vector<Test> tests;
};

// Test macros
#define TEST(name) \
    void test_##name(); \
    static bool registered_##name = []() { \
        TestFramework::getInstance().addTest(#name, test_##name); \
        return true; \
    }(); \
    void test_##name()

#define ASSERT_EQ(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            throw std::runtime_error("Expected " + std::to_string(expected) + " but got " + std::to_string(actual)); \
        } \
    } while(0)

#define ASSERT_STR_EQ(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            throw std::runtime_error("Expected '" + std::string(expected) + "' but got '" + std::string(actual) + "'"); \
        } \
    } while(0)

#define ASSERT_TRUE(condition) \
    do { \
        if (!(condition)) { \
            throw std::runtime_error("Expected true but got false"); \
        } \
    } while(0)

#define ASSERT_FALSE(condition) \
    do { \
        if (condition) { \
            throw std::runtime_error("Expected false but got true"); \
        } \
    } while(0)

#define RUN_ALL_TESTS() \
    int main() { \
        TestFramework::getInstance().runAllTests(); \
        return 0; \
    }

#endif // TESTFRAMEWORK_H