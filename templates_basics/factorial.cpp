#include <iostream>

template<int Value>
float Factorial() {
    return Value * Factorial<Value-1>();
}

template<>
float Factorial<0>() {
    return 1;
}

int main(int argc, char** argv) {
    std::cout << Factorial<4>() << "\n";
    return 0;
}