# execute via `curl -s https://raw.githubusercontent.com/asynts/stack-overflow/master/52234342/0001.sh | sh`
FILE=$(mktemp -t XXXXXXXX.cpp)
cat > $FILE <<EOF
#include <vector>
typedef struct {
  typedef struct {
  } test_t;
  std::vector<test_t> t;
} test2_t;
EOF
g++ --version
g++ -std=c++1z -Wall -Wextra -pedantic-errors -c $FILE -o $FILE.o
