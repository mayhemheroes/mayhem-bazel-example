#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <gtest/gtest.h>

extern "C" {
  #include "main/calculator.h"
}
// Simple unit test:
//   "with this specific input, we expect this specific output"

TEST(CalculatorTest, TestAdd) {
  EXPECT_EQ(add(1, 2), 3);
}

TEST(CalculatorTest, TestSubtract) {
  EXPECT_EQ(subtract(2, 1), 1);
}

TEST(CalculatorTest, TestMultiply) {
  EXPECT_EQ(multiply(3, 2), 6);
}