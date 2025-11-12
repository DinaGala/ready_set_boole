
#include "add.hpp"

// Iterative bitwise addition for 32-bit unsigned integers:
// - XOR: a ^ b
// - carry: (a & b) << 1
// Repeat until carry becomes 0. Uses only allowed operators.
uint32_t adder(uint32_t a, uint32_t b) {
    while (b != 0u) {
        uint32_t carry = (a & b) << 1u;
        a = a ^ b;
        b = carry;
    }
    return a;
}
