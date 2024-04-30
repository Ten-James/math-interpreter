//
// Created by james on 3/27/24.
//

#ifndef OOP2_PARSER_H
#define OOP2_PARSER_H
#include "lexer.h"
#include "ast/AstNode.h"
#include <vector>

/*
 *
 * GRAMATIKA
 *
 * expr -> term ((PLUS | MINUS) term)*
 * term -> factor ((MUL | DIV) factor)*
 * factor -> MINUS factor | NUM | LPAREN expr RPAREN
 *
 *
 *
 *
 *
 */


class parser {
    std::vector<token> tokens;
    int pos = 0;
    token current_token;
    void error();
    void advance();
    void eat(token_type type);
    AstNode* factor();
    AstNode* term();
    AstNode* expr();
public:
    parser();
    void reset(std::vector<token> tokens);
    AstNode* parse();

};


#endif //OOP2_PARSER_H
