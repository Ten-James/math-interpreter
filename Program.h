//
// Created by james on 3/27/24.
//

#ifndef OOP2_PROGRAM_H
#define OOP2_PROGRAM_H
#include "lexer.h"
#include "parser.h"
#include "io.h"


class Program {
    lexer lex;
    parser parse;
    io inputOutput;
public:
    void run();
    void run(std::string text);

};


#endif //OOP2_PROGRAM_H
