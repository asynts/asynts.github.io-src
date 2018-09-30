DIR=$(mktemp -d)

cat > $DIR/test.hpp <<EOF
typedef struct {
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

FLAGS="-O0 -Wall -Wextra -pedantic-errors"

g++ --version
g++ $FLAGS -c $DIR/test.cpp -o $DIR/test.o
g++ $FLAGS -c $DIR/main.cpp -o $DIR/main.o
g++ $FLAGS $DIR/main.o $DIR/test.o -o $DIR/main.out
nm -gC $DIR/main.out
