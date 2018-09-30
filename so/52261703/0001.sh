DIR=$(mktemp -d)

cat > $DIR/main.cpp <<EOF
#include <type_traits>
using namespace std;

template <typename ...>
class A;

template <>
struct A<> { };

template <typename T, typename ...TS>
struct A<T, TS...> : public A<TS...> {
  template <typename A = T>
  void something(A, std::enable_if_t<std::is_same_v<A, T>>* = 0) { }
};

int main() {
  A<char, short> a;
  a.something<short>(10); // error
}
EOF

g++ --version
g++ -std=c++1z -Wall -Wextra -pedantic-errors $DIR/main.cpp -o $DIR/main
