DIR=$(mktemp -d)

# inlining the source in the script
cat > $DIR/main.cpp <<EOF
#include <iostream>

struct Color{
    int r,g,b;
};

void printColor(Color color) {
    //printing color
}

class Test {
    static constexpr Color color = {242,34,4};
public:
    void print(){
        printColor(color);
    }
};


int main() {
    Test test;
    test.print();

    return 0;
}
EOF

# invoke the compiler
g++ --version
g++ -std=c++1z -Wall -Wextra -pedantic-errors $DIR/main.cpp -o $DIR/main
