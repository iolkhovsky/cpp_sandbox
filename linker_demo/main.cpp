#include <iostream>

#include "custom_ops.h"
#include "custom_exec.h"

int main(int argc, char** argv) {
    std::cout << "Runtime value 4! = " << RuntimeFactorial(4).value << "\n";
    std::cout << "Compile time value 4! = " << CompileTimeFactorial<4>::value << "\n";

    std::string s = "ubuntu";
    std::cout << "Reverse of " << s << " : " << reverseString(s) << "\n";
    return 0;
}
