//
// Created by james on 3/27/24.
//

#ifndef OOP2_PROGRAM_H
#define OOP2_PROGRAM_H
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "io/io.h"


class Program {
    lexer lex;
    parser parse;
    io inputOutput;
public:
    void run();
    void run(std::string text);
    void whileLoop();

};


#endif //OOP2_PROGRAM_H
