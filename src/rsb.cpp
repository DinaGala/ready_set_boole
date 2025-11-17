#include "../inc/rsb.hpp"

namespace rsb {

    // ex00
    // Iterative bitwise addition for 32-bit unsigned integers:
    // - XOR: a ^ b
    // - carry: (a & b) << 1
    // Repeat until carry becomes 0. Uses only allowed operators.
    uint32_t adder(uint32_t a, uint32_t b) {
        // for (int i = 0; i < 32; i++) FOR O(1) COMPLEXITY
        while (b != 0u) {
            uint32_t carry = (a & b) << 1u;
            a = a ^ b;
            b = carry;
        }
        return a;
    }

    // ex01
    uint32_t multiplier(uint32_t a, uint32_t b) {
        uint32_t result = 0u;
        // for (int i = 0; i < 32; i++) FOR O(1) COMPLEXITY
        while (b != 0u) {
            if (b & 1u) 
                result = adder(result, a);
            b >>= 1;
            a <<= 1;
        }
        return result;
    }

    // ex02
    uint32_t gray_code(uint32_t n) {
        return n ^ (n >> 1);
    }

    bool eval_formula(const std::string &formula) {
        std::shared_ptr<ASTNode> root = parse_rpn(formula);
        if (!root) {
            std::cerr << "Invalid formula\n";
            return false; // or throw an exception
        }
        if (root) {
            std::cout << "AST: ";
            root->print(root);
            std::cout << "\nEvaluation: " << std::boolalpha << root->eval() << std::endl;
        }
        return root->eval();
    }

    std::shared_ptr<ASTNode> parse_rpn(const std::string &formula) {
        std::stack<std::shared_ptr<ASTNode>> s;
        for (char c : formula) {
            switch(c) {
                case '0': s.push(std::make_shared<ASTNode>(false)); break;
                case '1': s.push(std::make_shared<ASTNode>(true)); break;
                case '!': {
                    if (s.empty()) return nullptr;
                    std::shared_ptr<ASTNode> e = s.top(); s.pop();
                    s.push(std::make_shared<ASTNode>(NodeType::NOT, e));
                    break;
                }
                case '&': case '|': case '^': case '>': case '=': {
                    if (s.size() < 2) return nullptr;
                    std::shared_ptr<ASTNode> b = s.top(); s.pop();
                    std::shared_ptr<ASTNode> a = s.top(); s.pop();
                    NodeType t = (c == '&') ? NodeType::AND :
                                (c == '|') ? NodeType::OR :
                                (c == '^') ? NodeType::XOR :
                                (c == '>') ? NodeType::IMPLIES :
                                NodeType::EQUIV;
                    s.push(std::make_shared<ASTNode>(t, a, b));
                    break;
                }
                default: return nullptr;
            }
        }
        return (s.size() == 1) ? s.top() : nullptr;
    }

} 