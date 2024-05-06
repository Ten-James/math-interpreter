//
// Created by james on 3/27/24.
//

#include <stdexcept>
#include <utility>
#include "lexer.h"

lexer::lexer() {
    this->text = "";
    this->pos = 0;
    this->current_char = '\0';
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
        case COMMA:
            return ',';
        case EQ:
            return '=';
        case ID:
            return 'i';
        case END:
            return '\0';
    }
    return '\0';
}

void lexer::reset(std::string text) {
    this->text = std::move(text);
    this->pos = 0;
}

std::vector<token> lexer::lex() {
    std::vector<token> tokens;
    size_t max = text.size();
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
            case ',':
                tokens.push_back(token {COMMA, 0});
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
            case '=':
                tokens.push_back(token {EQ, 0});
                this->advance();
                break;
            default:
                if (this->current_char >= '0' && this->current_char <= '9') {
                    tokens.push_back(token {NUM, this->number()});
                }
                else if (this->current_char >= 'a' && this->current_char <= 'z')
                {
                    tokens.push_back(token {ID,
                        .id = this->id()
                    });
                }
                else {
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

double lexer::number() {
    //lex number in [0-9]+(.[0-9]+)?
    std::string result;
    while (this->current_char >= '0' && this->current_char <= '9') {
        result += this->current_char;
        this->advance();
    }

    if (this->current_char == '.') {
        result += this->current_char;
        this->advance();

        while (this->current_char >= '0' && this->current_char <= '9') {
            result += this->current_char;
            this->advance();
        }
    }

    return std::stod(result);
}

std::string lexer::id()
{
    std::string result;
    while (this->current_char >= 'a' && this->current_char <= 'z')
    {
        result += this->current_char;
        this->advance();
    }
    return result;
}