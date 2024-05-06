//
// Created by Jakub Indrák on 06.05.2024.
//

#include "ConstantDefinition.h"

#include "Interpreter.h"

ReturnValue ConstantDefinition::visit()
{
    return Interpreter::interpret(this->value);
}
