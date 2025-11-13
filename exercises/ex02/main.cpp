#include <iostream>
#include <limits>
#include <cstdint>
#include "../../inc/rsb.hpp"

int main() {

    using namespace rsb;

    for (unsigned int i = 0; i <= 8; ++i) {
        std::cout << "n = " << i << " -> Gray code = " << gray_code(i) << std::endl;
    }
    return 0;


    return 0;
}
