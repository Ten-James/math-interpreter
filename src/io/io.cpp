//
// Created by james on 3/27/24.
//

#include "io.h"
#include <iostream>

std::string io::readText() {
    std::string text;
    std::cout << ">";
    std::getline(std::cin, text);
    return text;

}

void io::printResult(ReturnValue result)
{
    if (result.isReturn) {
        std::cout << result.value << std::endl;
    } else {
        std::cout << "Invalid expression" << std::endl;
    }
}

void io::printError(const char* error)
{
    std::cout << "[ERR] " << error << std::endl;
}


void io::printAst(AstNode *node) {
    if (node == nullptr) {
        return;
    }
    node->print("");
    std::cout << std::endl;
}
