#include <vector>

using std::vector;

void main() {
  // create a vector
  vector<int> hello;

  // assign some values
  hello = { 1, 2, 3 };

  // append a value to the vector
  hello.push_back(4);

  // 'hello' will automatically be deleted when the function returns
}

