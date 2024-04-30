//
// Created by james on 3/27/24.
//

#ifndef OOP2_LEXER_H
#define OOP2_LEXER_H

#include <vector>
#include <string>

enum token_type {
    NUM,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LPAREN,
    RPAREN,
    END
};

struct token {
    token_type type;
    int value;
};

class lexer {
    std::string text;
    int pos = 0;
    char current_char;
    void error();
    void advance();
    void skip_whitespace();
    int integer();
public:
    lexer();

    void reset(std::string text);

    std::vector<token> lex();

};

std::string token_type_to_string(token_type type);
char token_to_char(token_type type);


#endif //OOP2_LEXER_H
