#pragma once

#include <string>

template<int N>
struct CompileTimeFactorial {
    enum {
        value = CompileTimeFactorial<N-1>::value * N
    };
};

template<>
struct CompileTimeFactorial<0> {
    enum {
        value = 1
    };
};

struct RuntimeFactorial {
    RuntimeFactorial(int N);
    int value;
};

std::string reverseString(const std::string& s);
