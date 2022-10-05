#include <iostream>

template <class T>
T Sum(const T& a) {
    return a;
}

template<class First, class... Args>
auto Sum(const First& a, const Args&... others) {
    return a + Sum(others...);
}

int main(int argc, char** argv) {
    std::cout << Sum(-1., 2, 3, 4.5) << "\n";
    return 0;
}