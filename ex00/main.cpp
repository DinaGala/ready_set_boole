#include <iostream>
#include <limits>
#include <cstdint>
#include "add.hpp"

int main() {
    uint32_t a, b;

    a = 0u; b = 0u;
    std::cout << a << " + " << b << " = " << adder(a,b) << '\n';

    a = 1u; b = 1u;
    std::cout << a << " + " << b << " = " << adder(a,b) << '\n';

    a = 123456789u; b = 987654321u;
    std::cout << a << " + " << b << " = " << adder(a,b) << '\n';

    a = std::numeric_limits<uint32_t>::max();
    b = 0u;
    std::cout << "MAX + 0 = " << adder(a,b) << "\n";

    a = std::numeric_limits<uint32_t>::max();
    b = 1u;
    std::cout << "MAX + 1 (wrap) = " << adder(a,b) << "\n";

    // Interactive small check
    std::cout << "Enter two non-negative integers (a b): ";
    if (std::cin >> a >> b) {
        std::cout << a << " + " << b << " = " << adder(a,b) << '\n';
    }

    return 0;
}
