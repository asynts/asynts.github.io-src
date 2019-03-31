#include <stddef.h>
#include <stdio.h>

struct A {
  char a;
  int b;
};

int main() {
  // refer to https://en.cppreference.com/w/c/types/offsetof
  printf("offsetof(A, b) = %zu\n", offsetof(struct A, b));
}

