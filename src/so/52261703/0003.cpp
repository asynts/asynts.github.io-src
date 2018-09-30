#include <type_traits>
#include <iostream>
using namespace std;

template <typename ...>
class A;

// Handle the edge case.
template <>
struct A<> {
  // Edge case for `using<TS...>::something`.
  template <typename T>
  void something(T, std::enable_if_t<!std::is_same_v<T, T>>* = 0) { }
};

// Required so that `something()` can only be called with a type
// that appears in the template arguments.
template <typename T, typename ...TS>
struct A<T, TS...> : public A<TS...> {
  // Make the previous method visible.
  using A<TS...>::something;

  // Allow user to explicitly specify T.
  template <typename B = T>
  void something(B, std::enable_if_t<std::is_same_v<B, T>>* = 0) {
    // Figure out which method was called.
    cout << __PRETTY_FUNCTION__ << endl;
  }
};

int main() {
  A<char, short> a;

  // Explicitly call `A<char, short>::something(char)`
  a.something<char>(10);

  // Explicitly call `A<short>::something(short)`
  a.something<short>(10);
}
