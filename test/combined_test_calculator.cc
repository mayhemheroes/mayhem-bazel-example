#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <gtest/gtest.h>

extern "C" {
  #include "main/calculator.h"
}

void test_add(int x, int y) {
  EXPECT_TRUE(add(x, y) == x + y);
}

void test_subtract(int x, int y) {
  EXPECT_TRUE(subtract(x, y) == x - y);
}

void test_multiply(int x, int y) {
  EXPECT_TRUE(multiply(x, y) == x * y);
}

void test_divide(int x, int y) {
  EXPECT_TRUE(divide(x, y) == x / y);
}

void test_factor_game(int x, int y) {
  factor_game(x, y); // bug is hidden in factor_game() itself, no need for extra assert() here
}

TEST(CalculatorTest, TestAdd) {
  test_add(1, 2);
}

TEST(CalculatorTest, TestSubtract) {
  test_subtract(2, 1);
}

TEST(CalculatorTest, TestMultiply) {
  test_multiply(3, 2);
}

TEST(CalculatorTest, TestDivide) {
  test_divide(6, 2);
}

TEST(CalculatorTest, TestFactorGame) {
  test_factor_game(6, 2);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    // Check for file input
    if (argc > 1) {
        std::ifstream inputFile(argv[1]);
        if (!inputFile.is_open()) {
            std::cerr << "Failed to open input file: " << argv[1] << "\n";
            return 1;
        }

        int a, b;

        // Assume the input file contains our two variables
        inputFile >> a >> b;

        test_add(a, b);
        test_subtract(a, b);
        test_multiply(a, b);
        test_divide(a, b);
        test_factor_game(a, b);

        // Skip running the default tests since we're using file input
        return 0;
    }

    // If no file input is provided, run standard test fixtures
    return RUN_ALL_TESTS();
}