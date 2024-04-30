//
// Created by james on 3/27/24.
//

#ifndef OOP2_IO_H
#define OOP2_IO_H
#include "lexer.h"
#include "ast/AstNode.h"

class io {
public:
    void printTokens(std::vector<token> tokens);
    void printAst(AstNode* node);
    std::string readText();

};


#endif //OOP2_IO_H
