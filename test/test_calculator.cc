#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
  #include "main/calculator.h"
}

void test_add(int x, int y) {
  // assert(add(x, y) == x + y);
  add(x, y);
}

void test_subtract(int x, int y) {
  // assert(subtract(x, y) == x - y);
  subtract(x, y);
}

void test_multiply(int x, int y) {
  // assert(multiply(x, y) == x * y);
  multiply(x, y);
}

void test_divide(int x, int y) {
  // assert(divide(x, y) == x / y);
  divide(x, y);
}

void test_factor_game(int x, int y) {
  // assert(factor_game(x, y) == 0);
  factor_game(x, y);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <input_file>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    perror("Error opening file");
    return 1;
  }

  int x, y;
  char buf[64];
  fgets(buf, sizeof(buf), file);
  sscanf(buf, "%d %d", &x, &y);

  test_add(x, y);
  test_subtract(x, y);
  test_multiply(x, y);
  test_divide(x, y);
  test_factor_game(x, y);

  fclose(file);
  return 0;
}