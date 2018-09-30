DIR=$(mktemp -d)

cat > $DIR/test.hpp <<EOF
#include <vector>
typedef struct {
  typedef struct { } B;

  std::vector<B> b;
  void a();
} A;
EOF

cat > $DIR/test.cpp <<EOF
#include "test.hpp"
void A::a() { }
EOF

cat > $DIR/main.cpp <<EOF
#include "test.hpp"
int main() {
  A a;
}
EOF

FLAGS="-flto -Wall -Wextra -pedantic-errors"

g++ --version
g++ $FLAGS -c $DIR/test.cpp -o $DIR/test.o
g++ $FLAGS -c $DIR/main.cpp -o $DIR/main.o
g++ $FLAGS $DIR/main.o $DIR/test.o -o $DIR/main.out
