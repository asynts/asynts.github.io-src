#include <stdio.h>

struct A {
  int x;
};

struct B {
  int x;
};

int main() {
  struct A a = {1};

  // p points to a structure of type A
  void *p = &a;

  // p points to a structure of type B, since A's initial member can be
  // contained in B
  struct B *b = p;

  printf("a.x = %d\n", b->x);
}

