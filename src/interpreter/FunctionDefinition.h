//
// Created by Jakub Indrák on 06.05.2024.
//

#ifndef FUNCTIONDEFINITION_H
#define FUNCTIONDEFINITION_H
#include "Definition.h"
#include <utility>
#include <vector>


class FunctionDefinition: public Definition {
private:
    std::vector<std::string> args;
public:
    ReturnValue visit() override;
    ReturnValue visit(const AstFunction* function);
    FunctionDefinition(std::string name, std::vector<std::string> args, AstNode* value): Definition(std::move(name), value), args(std::move(args)) {}
    std::vector<std::string>& get_args() { return args; }

};



#endif //FUNCTIONDEFINITION_H
