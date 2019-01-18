#include <stdio.h>

struct A {
  // x is A's initial member
  int x;

  int y;
};

int main() {
  struct A a;

  // the address of a structure points to it's initial element
  printf("a is located at   %p\n", &a);
  printf("a.x is located at %p\n", &a.x);
}

