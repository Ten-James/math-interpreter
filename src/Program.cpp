//
// Created by james on 3/27/24.
//

#include "Program.h"

#include "interpreter/Interpreter.h"

void Program::run() {
    std::string text = inputOutput.readText();
    this->run(text);

}

void Program::run(std::string text) {
    lex.reset(text);
    AstNode* tree;
    try
    {
        auto tokens = lex.lex();
        parse.reset(tokens);
        tree = parse.parse();
    }
    catch (std::runtime_error &e)
    {
        inputOutput.printError(e.what());
        return;
    }
    //inputOutput.printAst(tree);

    try {
        if (tree->get_type() == DEFINITION)
        {
            auto def = dynamic_cast<AstDefinition*>(tree);
            auto res = Interpreter::add_definition(def);
            inputOutput.printResult(res);
        }
        else if (tree->get_type() == FUN_DEFINITION)
        {
            auto def = dynamic_cast<AstFunDefinition*>(tree);
            Interpreter::add_definition(def);
        }
        else
        {
            auto res =Interpreter::interpret(tree);
            inputOutput.printResult(res);
        }
    }
    catch (std::runtime_error &e)
    {
        inputOutput.printError(e.what());
        return;
    }
    delete tree;
}

void Program::whileLoop()
{
    while (true) {
        auto text = inputOutput.readText();
        if (text == "exit") {
            break;
        }
        this->run(text);
    }
}
