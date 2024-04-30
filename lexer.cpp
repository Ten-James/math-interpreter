//
// Created by james on 3/27/24.
//

#include <stdexcept>
#include "lexer.h"

lexer::lexer() {
    this->text = "";
    this->pos = 0;
}

std::string token_type_to_string(token_type type) {
    switch (type) {
        case NUM:
            return "NUM";
        case PLUS:
            return "PLUS";
        case MINUS:
            return "MINUS";
        case MUL:
            return "MUL";
        case DIV:
            return "DIV";
        case LPAREN:
            return "LPAREN";
        case RPAREN:
            return "RPAREN";
        case END:
            return "END";

    }
}

char token_to_char(token_type type) {
    switch (type) {
        case NUM:
            return '0';
        case PLUS:
            return '+';
        case MINUS:
            return '-';
        case MUL:
            return '*';
        case DIV:
            return '/';
        case LPAREN:
            return '(';
        case RPAREN:
            return ')';
        case END:
            return '\0';
    }
}

void lexer::reset(std::string text) {
    this->text = text;
    this->pos = 0;
}

std::vector<token> lexer::lex() {
    std::vector<token> tokens;
    int max = this->text.size();
    this->current_char = this->text[this->pos];
    while (this->pos < max) {
        switch (this->current_char) {
            case ' ':
            case '\n':
            case '\t':
                this->skip_whitespace();
                break;
            case '+':
                tokens.push_back(token {PLUS, 0});
                this->advance();
                break;
            case '-':
                tokens.push_back(token {MINUS, 0});
                this->advance();
                break;
            case '*':
                tokens.push_back(token {MUL, 0});
                this->advance();
                break;
            case '/':
                tokens.push_back(token {DIV, 0});
                this->advance();
                break;
            case '(':
                tokens.push_back(token {LPAREN, 0});
                this->advance();
                break;
            case ')':
                tokens.push_back(token {RPAREN, 0});
                this->advance();
                break;
            default:
                if (this->current_char >= '0' && this->current_char <= '9') {
                    tokens.push_back(token {NUM, this->integer()});
                } else {
                    this->error();
                }
        }

    }
    tokens.push_back(token {END, 0});
    return tokens;
}

void lexer::error() {
    throw std::runtime_error("Invalid character");
}

void lexer::advance() {
    this->pos++;
    if (this->pos < this->text.size()) {
        this->current_char = this->text[this->pos];
    } else {
        this->current_char = '\0';
    }

}

void lexer::skip_whitespace() {
    while (this->current_char == ' ' || this->current_char == '\n' || this->current_char == '\t') {
        this->advance();
    }
}

int lexer::integer() {
    int result = 0;
    while (this->current_char >= '0' && this->current_char <= '9') {
        result = result * 10 + (this->current_char - '0');
        this->advance();
    }
    return result;
}
