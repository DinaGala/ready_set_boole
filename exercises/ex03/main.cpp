#include <iostream>
#include <limits>
#include <cstdint>
#include "../../inc/rsb.hpp"

int main() {

    using namespace rsb;

    std::string formula = "101|&"; // Example: ⊤ ∧ (⊥ ∨ ⊤)
    std::cout << "\nFormula: " << formula << std::endl;
    bool result = eval_formula(formula);
    std::cout << "Result: " << formula << " => " << result << std::endl;


    std::string formulas[] = {
        "10&",      // ⊤ ∧ ⊥ -> false
        "10|",      // ⊤ ∨ ⊥ -> true
        "11>",      // ⊤ ⇒ ⊤ -> true
        "10=",      // ⊤ ⇔ ⊥ -> false
        "1011||="   // ⊤ ∨ ⊥ ∨ ⊤ -> true
    };

    for (const auto &f : formulas) {
        std::cout << "\nFormula: " << f << std::endl;
        bool result = eval_formula(f);
        std::cout << "Result: " << f << " => " << std::boolalpha << result << std::endl;
    }

    return 0;
}
