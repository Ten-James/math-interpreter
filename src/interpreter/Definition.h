//
// Created by Jakub Indrák on 06.05.2024.
//

#ifndef DEFINITION_H
#define DEFINITION_H
#include <utility>

#include "ReturnValue.h"
#include "../ast/AstNode.h"


class Definition {
public:
    std::string name;
    AstNode* value;
    Definition(std::string name, AstNode* value) : name{std::move(name)}, value{value} {};
    virtual ReturnValue visit() = 0;
    virtual ~Definition() = default;
};



#endif //DEFINITION_H
