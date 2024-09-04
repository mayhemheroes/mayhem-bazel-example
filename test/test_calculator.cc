#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
  #include "main/calculator.h"
}

// Dynamic testing with Mayhem: 
//   "with any given input, what happens? (Implicitly, we expect no crashes)"

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

  int x, y, s;
  char buf[64];
  fgets(buf, sizeof(buf), file);
  sscanf(buf, "%d %d %d", &x, &y ,&s);

  switch (s % 3) {
    case 0:
      test_add(x, y);
      break;
    case 1:
      test_subtract(x, y);
      break;
    case 2:
      test_multiply(x, y);
      break;
    default:
      return 0;
  }

  fclose(file);
  return 0;
}