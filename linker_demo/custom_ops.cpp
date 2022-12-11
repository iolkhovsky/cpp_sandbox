#include "custom_ops.h"

RuntimeFactorial::RuntimeFactorial(int N)
: value(N == 0 ? 1 : RuntimeFactorial(N-1).value * N)
{} 

std::string reverseString(const std::string& s) {
    return {s.rbegin(), s.rend()};
}
