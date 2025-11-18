#pragma once

#include <cstdint>
#include <memory>
#include <iostream>
#include <stack>
#include <string>

enum class NodeType {
    CONST, NOT, AND, OR, XOR, IMPLIES, EQUIV
};

struct ASTNode {
    NodeType type;
    bool value; // used if type == CONST
    char var;   // variable name if needed
    std::shared_ptr<ASTNode> left;   // for binary operators
    std::shared_ptr<ASTNode> right;  // for binary operators
    std::shared_ptr<ASTNode> child;  // for unary operator NOT

    ASTNode(bool val) : type(NodeType::CONST), value(val) {}
    ASTNode(NodeType t, std::shared_ptr<ASTNode> c) : type(t), child(c) {}
    ASTNode(NodeType t, std::shared_ptr<ASTNode> l, std::shared_ptr<ASTNode> r) 
        : type(t), left(l), right(r) {}

    bool eval() {
        switch(this->type) {
            case NodeType::CONST:
                if (var >= 'A' && var <= 'Z')
                    return env.at(var);   // variable
                return value;             // real constant (0 or 1)
            case NodeType::NOT: return !this->child->eval();
            case NodeType::AND: return this->left->eval() && this->right->eval();
            case NodeType::OR: return this->left->eval() || this->right->eval();
            case NodeType::XOR: return this->left->eval() != this->right->eval();
            case NodeType::IMPLIES: return !this->left->eval() || this->right->eval();
            case NodeType::EQUIV: return this->left->eval() == this->right->eval();
        }
        return false; // should never reach
    }

    void print(const std::shared_ptr<ASTNode>& node) {
        switch(node->type) {
            case NodeType::CONST: std::cout << (node->value ? "⊤" : "⊥"); break;
            case NodeType::NOT: std::cout << "¬("; print(node->child); std::cout << ")"; break;
            case NodeType::AND: std::cout << "("; print(node->left); std::cout << " ∧ "; print(node->right); std::cout << ")"; break;
            case NodeType::OR: std::cout << "("; print(node->left); std::cout << " ∨ "; print(node->right); std::cout << ")"; break;
            case NodeType::XOR: std::cout << "("; print(node->left); std::cout << " ⊕ "; print(node->right); std::cout << ")"; break;
            case NodeType::IMPLIES: std::cout << "("; print(node->left); std::cout << " ⇒ "; print(node->right); std::cout << ")"; break;
            case NodeType::EQUIV: std::cout << "("; print(node->left); std::cout << " ⇔ "; print(node->right); std::cout << ")"; break;
        }
    }

};

namespace rsb {

    // ex00 - adder: bitwise addition (no +)
    uint32_t adder(uint32_t a, uint32_t b);

    // ex01 - multiplier: uses adder
    uint32_t multiplier(uint32_t a, uint32_t b);

    // ex02 - gray code
    uint32_t gray_code(uint32_t n);

    // ex03 - boolean formula evaluation
    bool eval_formula(const std::string &formula);
    std::shared_ptr<ASTNode> parse_rpn(const std::string &formula);

    // ex04 - truth table
    void print_truth_table(const std::string &formula);
    
} 