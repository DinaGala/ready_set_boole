#include <iostream>
#include <limits>
#include <cstdint>
#include "../../inc/rsb.hpp"

int main() {

    using namespace rsb;

    std::string formula = "101|&"; // Example: ⊤ ∧ (⊥ ∨ ⊤)
    bool result = eval_formula(formula);

    std::cout << "Result: " << std::boolalpha << result << std::endl;

    return 0;
}
