// gcc -Wall -Wextra -pedantic-errors 0002.c -o 0002.out
#include <stdlib.h>
#include <stdio.h>

int main() {
  size_t size = 10;

  // only one malloc call
  char *buf = malloc(size * size);

  // access buf[1][2] (contains junk)
  printf("%02x\n", buf[1 * size + 2]);
}
