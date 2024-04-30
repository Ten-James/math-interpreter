//
// Created by james on 3/27/24.
//

#ifndef OOP2_ASTNODE_H
#define OOP2_ASTNODE_H


#include <iostream>

class AstNode {
    public:
    virtual void print(std::string offset) = 0;

};

class AstOperator : public AstNode {
    char op;
    AstNode *left;
    AstNode *right;
public:
    AstOperator(char op, AstNode *left, AstNode *right) : op(op), left(left), right(right) {}
    ~AstOperator() {
        delete left;
        delete right;
    }
    void print(std::string offset) {
        std::cout << offset;
        std::cout << op;
        std::cout << std::endl;
        std::cout << offset;
        left->print(offset + " ");
        std::cout << std::endl;
        std::cout << offset;
        right->print(offset + " ");
    }
    char getOp() const {
        return op;
    }
    AstNode* getLeft() {
        return left;
    }
    AstNode* getRight() {
        return right;
    }
};

class AstNumber : public AstNode {
    int value;
public:
    AstNumber(int value) : value(value) {}
    void print(std::string offset) {
        std::cout << offset;
        std::cout << value;
    }
    int getValue() const {
        return value;
    }
};

class AstUnary : public AstNode {
    char op;
    AstNode *expr;
public:
    AstUnary(char op, AstNode *expr) : op(op), expr(expr) {}
    ~AstUnary() {
        delete expr;
    }
    void print(std::string offset) {
        std::cout << offset;
        std::cout << "Unary: ";
        std::cout << op;
        std::cout << std::endl;
        std::cout << offset;
        expr->print(offset + " ");
    }
    char getOp() const {
        return op;
    }
    AstNode* getExpr() {
        return expr;
    }
};


#endif //OOP2_ASTNODE_H
