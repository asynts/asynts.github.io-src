// gcc -Wall -Wextra -pedantic-errors 0001.c -o 0001.out
#include <stdlib.h>
#include <stdio.h>

int main() {
  size_t size = 10;

  char **buf = malloc(sizeof(char*) * size);
  for(size_t i=0; i<size; i++) {
    buf[i] = malloc(size);
  }

  // access buf[1][2] (contains junk)
  printf("%02x\n", buf[1][2]);
}
