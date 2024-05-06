//
// Created by Jakub Indrák on 06.05.2024.
//

#include "FunctionDefinition.h"

#include "ConstantDefinition.h"
#include "Interpreter.h"
#include "../io/io.h"

ReturnValue FunctionDefinition::visit()
{
    return Interpreter::interpret(value);
}

ReturnValue FunctionDefinition::visit(const AstFunction* function)
{
    std::vector<Definition*> scope;
    if (args.size() != function->get_args().size())
    {
        throw std::runtime_error("Invalid number of arguments");
    }
    for (size_t i = 0; i < args.size(); i++)
    {
        scope.push_back(new ConstantDefinition(args[i], function->get_args()[i]->copy()));
    }

    // std::cout << "------------------" << std::endl;
    // for (auto& def : scope)
    // {
    //     std::cout << def->name << std::endl;
    //     auto ouput = io();
    //     ouput.printAst(def->value);
    // }
    // std::cout << "------------------" << std::endl;

    auto value = Interpreter::interpret(this->value, scope);
    return value;
}
