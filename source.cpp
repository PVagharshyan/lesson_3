#include "string.h"

#include <iostream>

int main() { 
    String s = "Hello";
    String s1 = std::move(s);
    std::cout << s << std::endl;
    return 0;
}
