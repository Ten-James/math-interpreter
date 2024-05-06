//
// Created by Jakub Indrák on 06.05.2024.
//

#ifndef CONSTANTDEFINITION_H
#define CONSTANTDEFINITION_H
#include "Definition.h"

#include <utility>


class ConstantDefinition : public Definition {
public:
    ReturnValue visit() override;
    ConstantDefinition(std::string name, AstNode* value) : Definition{std::move(name), value} {}
};



#endif //CONSTANTDEFINITION_H
