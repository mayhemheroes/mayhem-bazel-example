#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
  #include "main/calculator.h"
}

// Let's turn it up a notch with some Mayhem! 
// We'll test:
//    * Basic algebra works as expected.
//    * We don't get runtime errors.

// test x + y = y + x
void test_add_commutes(int x, int y) {
   assert(add(x,y) == add(y,x));
}

// test x + y - y = x
void test_add_subtract(int x, int y) { 
   assert(subtract(add(x,y),y) == x);
}

// test x * y = y * x
void test_multiply_commutes(int x, int y) {
   assert(multiply(x,y) == multiply(y,x));
}

// test (x * x) / x =  x
//
// Mayhem finds a subtle vulnerability easily missed manually.
// Details: When x*x overflows, the result is negative.
//          dividing by x is still negative, thus
//          violating the assertion.  
//         example: x = 87570
void test_cancel_divisor(int x) {
  int product = multiply(x,x);
  assert(divide(product, x) == x);
}


// Mayhem can even solve puzzles like the factor game!
void test_factor_game(int x, int y) {
  assert(factor_game(x,y) == 0);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdata(data, size);
  int x, y;
  uint8_t flag;

  x = fdata.ConsumeIntegralInRange<int>(-0x3fffffff, 0x3fffffff);
  y = fdata.ConsumeIntegralInRange<int>(-0x3fffffff, 0x3fffffff);
  flag = fdata.ConsumeIntegralInRange<uint8_t>(0, 4);

  switch(flag) {
    case 0:
      test_add_commutes(x,y);
      break;
    case 1:
      test_add_subtract(x,y);
      break;
    case 2:
      test_multiply_commutes(x,y);
      break;
    case 3:
      test_cancel_divisor(x);
      break;
    case 4:
      test_factor_game(x,y);
      break;
  }
  return 0;
}
