//
// Created by james on 3/27/24.
//

#include "Program.h"

void Program::run() {
    std::string text = inputOutput.readText();
    this->run(text);

}

void Program::run(std::string text) {
    lex.reset(text);
    std::vector<token> tokens = lex.lex();
    //inputOutput.printTokens(tokens);
    parse.reset(tokens);
    AstNode* tree = parse.parse();
    inputOutput.printAst(tree);

}
