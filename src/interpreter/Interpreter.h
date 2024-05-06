//
// Created by Jakub Indrák on 30.04.2024.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "ReturnValue.h"
#include "Definition.h"
#include "../ast/AstNode.h"
#include <vector>




class Interpreter {
private:
    static std::vector<Definition*> definitions;
    static ReturnValue visit(AstNode* node, std::vector<Definition*> local_scope = {});
public:
    static ReturnValue interpret(AstNode* node, std::vector<Definition*> local_scope = {});
    static ReturnValue add_definition(AstDefinition* definition);
    static ReturnValue add_definition(AstFunDefinition* definition);
};



#endif //INTERPRETER_H
