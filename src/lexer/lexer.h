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
    COMMA,
    LPAREN,
    RPAREN,
    EQ,
    ID,
    END
};

struct token {
    token_type type;
    double value;
    std::string id;
};

class lexer {
    std::string text;
    size_t pos = 0;
    char current_char;
    void error();
    void advance();
    void skip_whitespace();
    double number();
    std::string id();
public:
    lexer();

    void reset(std::string text);

    std::vector<token> lex();

};

char token_to_char(token_type type);


#endif //OOP2_LEXER_H
