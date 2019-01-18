#include <stdio.h>

struct A {
  int x;
};

int main() {
  struct A a = {1};

  // b points to a structure of type A
  void *b = &a;

  // b points to an integer, since A's initial element is an integer
  int *c = b;

  printf("a.x = %d\n", *c);
}

