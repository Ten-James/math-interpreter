//
// Created by james on 3/27/24.
//

#ifndef OOP2_IO_H
#define OOP2_IO_H
#include "../lexer/lexer.h"
#include "../ast/AstNode.h"
#include "../interpreter/Interpreter.h"

class io {
public:
    void printAst(AstNode* node);
    std::string readText();
    void printResult(ReturnValue result);
    void printError(const char* error);

};


#endif //OOP2_IO_H
