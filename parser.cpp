//
// Created by james on 3/27/24.
//

#include <stdexcept>
#include "parser.h"

void parser::reset(std::vector<token> tokens) {
    this->tokens = tokens;
    this->pos = 0;
    this->current_token = this->tokens[this->pos];
}

void parser::error() {
    throw std::runtime_error("Invalid syntax");
}

void parser::advance() {
    this->pos++;
    if (this->pos < this->tokens.size()) {
        this->current_token = this->tokens[this->pos];
    }
}

void parser::eat(token_type type) {
    if (this->current_token.type == type) {
        this->advance();
    } else {
        this->error();
    }
}

AstNode *parser::factor() {
    if (current_token.type == MINUS) {
        this->eat(MINUS);
        return new AstUnary('-', this->factor());
    } else if (current_token.type == NUM) {
        int value = current_token.value;
        this->eat(NUM);
        return new AstNumber(value);
    } else if (current_token.type == LPAREN) {
        this->eat(LPAREN);
        AstNode *node = this->expr();
        this->eat(RPAREN);
        return node;
    } else {
        this->error();
    }

}

AstNode *parser::term() {
    AstNode *node = this->factor();
    while (current_token.type == MUL || current_token.type == DIV) {
        token_type type = current_token.type;
        if (type == MUL) {
            this->eat(MUL);
        } else if (type == DIV) {
            this->eat(DIV);
        }
        node = new AstOperator(token_to_char(type), node, this->factor());
    }
    return node;
}

AstNode *parser::expr() {
    AstNode *node = this->term();
    while (current_token.type == PLUS || current_token.type == MINUS) {
        token_type type = current_token.type;
        if (type == PLUS) {
            this->eat(PLUS);
        } else if (type == MINUS) {
            this->eat(MINUS);
        }
        node = new AstOperator(token_to_char(type), node, this->term());
    }
    return node;
}

AstNode *parser::parse() {
    auto ret = this->expr();

    if (this->current_token.type != END) {
        this->error();
    }

    return ret;
}

parser::parser() {
    this->tokens = {};
    this->pos = 0;
    this->current_token = token {END, 0};
}


