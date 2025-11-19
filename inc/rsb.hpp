#pragma once

#include <cstdint>
#include <memory>
#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <stdexcept>

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

    bool contains_variable() const {
        if (type == NodeType::CONST && var >= 'A' && var <= 'Z') 
            return true;
        if (left && left->contains_variable()) 
            return true;
        if (right && right->contains_variable()) 
            return true;
        return false;
    }

    bool eval(const std::map<char,bool>& env) const {
        switch (type) {
            case NodeType::CONST:
                if (var >= 'A' && var <= 'Z') return env.at(var);
                return value;
            case NodeType::NOT: return !left->eval(env);
            case NodeType::AND: return left->eval(env) && right->eval(env);
            case NodeType::OR:  return left->eval(env) || right->eval(env);
            case NodeType::XOR: return left->eval(env) != right->eval(env);
            case NodeType::IMPLIES: return !left->eval(env) || right->eval(env);
            case NodeType::EQUIV: return left->eval(env) == right->eval(env);
        }
        return false;
    }

    bool eval() const {
        if (contains_variable()) 
            throw std::logic_error("eval() called on non-ground AST");
        std::map<char,bool> empty;
        return eval(empty);
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