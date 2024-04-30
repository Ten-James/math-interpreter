//
// Created by james on 3/27/24.
//

#include "io.h"
#include <iostream>

void io::printTokens(std::vector<token> tokens) {
    for (int i = 0; i < tokens.size(); i++) {
        std::cout << "{" << token_type_to_string(tokens[i].type);
        if (tokens[i].type == NUM) {
            std::cout << ": " << tokens[i].value;
        }
        std::cout << "}";
        std::cout << std::endl;
    }

}

std::string io::readText() {
    std::string text;
    std::cout << ">";
    std::getline(std::cin, text);
    return text;

}



void io::printAst(AstNode *node) {
    if (node == nullptr) {
        return;
    }
    node->print("");
}
