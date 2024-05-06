//
// Created by Jakub Indrák on 30.04.2024.
//

#include "Interpreter.h"

#include "ConstantDefinition.h"
#include "FunctionDefinition.h"

std::vector<Definition*> Interpreter::definitions;

ReturnValue Interpreter::visit(AstNode* node, std::vector<Definition*> local_scope)
{
    if (node == nullptr)
        return ReturnValue{
            .isReturn = false,
            .value = 0,
        };
    if (node->get_type() == NUMBER) {
        const auto* number = dynamic_cast<AstNumber*>(node);
        return ReturnValue{
            .isReturn = true,
            .value = number->get_value(),
        };
    }
    if (node->get_type() == UNARY)
    {
        const auto* unary = dynamic_cast<AstUnary*>(node);
        auto value = visit(unary->get_expr(), local_scope);
        if (unary->get_op() == '-')
        {
            return ReturnValue{
                .isReturn = true,
                .value = -value.value,
            };
        }

        throw std::runtime_error("Invalid unary operator");
    }

    if (node->get_type() == OPERATOR)
    {
        const auto* op = dynamic_cast<AstOperator*>(node);
        auto left = visit(op->get_left(), local_scope);
        auto right = visit(op->get_right(), local_scope);
        switch (op->get_op())
        {
            case '+':
                return ReturnValue{
                    .isReturn = true,
                    .value = left.value + right.value,
                };
            case '-':
                return ReturnValue{
                    .isReturn = true,
                    .value = left.value - right.value,
                };
            case '*':
                return ReturnValue{
                    .isReturn = true,
                    .value = left.value * right.value,
                };
            case '/':
                return ReturnValue{
                    .isReturn = true,
                    .value = left.value / right.value,
                };
            default:
                throw std::runtime_error("Invalid operator");
        }
    }

    if (node->get_type() == VARIABLE)
    {
        const auto* variable = dynamic_cast<AstVariable*>(node);

        for (int i = local_scope.size() - 1; i >= 0; i--)
        {
            if (local_scope[i]->name == variable->get_name())
            {
                return ReturnValue{
                    .isReturn = true,
                    .value = visit(local_scope[i]->value, local_scope).value,
                };
            }
        }

        for (int i = definitions.size() - 1; i >= 0; i--)
        {
            if (definitions[i]->name == variable->get_name())
            {
                return ReturnValue{
                    .isReturn = true,
                    .value = visit(definitions[i]->value, local_scope).value,
                };
            }

        }

        throw std::runtime_error("Variable not defined");
    }

    if (node->get_type() == FUNCTION)
    {
        const auto* function = dynamic_cast<AstFunction*>(node);

        for (int i = local_scope.size() -1; i >= 0; i--)
        {
            if (local_scope[i]->name == function->get_name())
            {
                auto fun = dynamic_cast<FunctionDefinition*>(local_scope[i]);
                return fun->visit(function);
            }
        }

        for (int i = definitions.size() - 1; i >= 0; i--)
        {
            if (definitions[i]->name == function->get_name())
            {
                auto fun = dynamic_cast<FunctionDefinition*>(definitions[i]);
                return fun->visit(function);
            }
        }
    }


    return ReturnValue{
        .isReturn = false,
        .value = 0,
    };

}

ReturnValue Interpreter::interpret(AstNode* node, std::vector<Definition*> local_scope)
{

    auto value = visit(node, local_scope);

    return value;
}

ReturnValue Interpreter::add_definition(AstDefinition* definition)
{
    Interpreter::definitions.push_back(new ConstantDefinition(definition->get_name(),definition->get_value()->copy()));
    auto value =  visit(definition->get_value());
    return value;
}

ReturnValue Interpreter::add_definition(AstFunDefinition* definition)
{
    definitions.push_back(new FunctionDefinition(definition->get_name(), definition->get_args(), definition->get_value()->copy()));
    return ReturnValue{
        .isReturn = true,
        .value = 0,
    };
}
