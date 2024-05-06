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
    throw std::runtime_error("Invalid syntax " + std::to_string(this->pos));
}
void parser::error(std::string message) {
    throw std::runtime_error(message + " " + std::to_string(this->pos));
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
        this->error("Expected " + std::string(1, token_to_char(type)) + " got " + std::string(1, token_to_char(this->current_token.type)) + " at position");
    }
}

AstNode *parser::factor() {
    if (current_token.type == MINUS) {
        this->eat(MINUS);
        return new AstUnary('-', this->factor());
    }
    if (current_token.type == NUM) {
        auto value = current_token.value;
        this->eat(NUM);
        return new AstNumber(value);
    }
    if (current_token.type == LPAREN) {
        this->eat(LPAREN);
        AstNode *node = this->expr();
        this->eat(RPAREN);
        return node;
    }
    if (current_token.type == ID) {
        std::string id = current_token.id;
        this->eat(ID);
        if (current_token.type == LPAREN)
        {
            this->eat(LPAREN);
            std::vector<AstNode*> args;
            if (current_token.type != RPAREN)
            {
                args.push_back(this->expr());
            }
            while (current_token.type == COMMA)
            {
                this->eat(COMMA);
                args.push_back(this->expr());
            }
            this->eat(RPAREN);
            return new AstFunction(id, args);
        }
        return new AstVariable(id);
    }

    this->error();
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

AstNode* parser::definition()
{
    if (current_token.type != ID)
    {
        return nullptr;
    }
    if (tokens[pos + 1].type == EQ)
    {
        std::string id = current_token.id;
        this->eat(ID);
        this->eat(EQ);
        return new AstDefinition(id, this->expr());
    }
    else if (tokens[pos + 1].type == LPAREN)
    {
        auto cur_pos = pos;
        std::string id = current_token.id;
        std::vector<std::string> args;
        this->eat(ID);
        this->eat(LPAREN);
        if (current_token.type == ID)
        {
            args.push_back(current_token.id);
            this->eat(ID);
        }
        else
        {
            pos = cur_pos;
            current_token = tokens[pos];
            return nullptr;
        }
        while (current_token.type == COMMA)
        {
            this->eat(COMMA);
            args.push_back(current_token.id);
            if (current_token.type != ID)
            {
                pos = cur_pos;
                current_token = tokens[pos];
                return nullptr;
            }
            this->eat(ID);
        }
        if (current_token.type != RPAREN)
        {
            pos = cur_pos;
            current_token = tokens[pos];
            return nullptr;
        }
        this->eat(RPAREN);
        if (current_token.type != EQ)
        {
            pos = cur_pos;
            current_token = tokens[pos];
            return nullptr;
        }
        this->eat(EQ);
        return new AstFunDefinition(id, this->expr(), args);
    }

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

AstNode *parser::line() {
    auto line =  this->definition();
    if (line != nullptr)
    {
        return line;
    }
    return this->expr();
}

AstNode *parser::parse() {
    auto ret = this->line();

    if (this->current_token.type != END) {
        this->error("Unexpected token at end");
    }

    return ret;
}

parser::parser() {
    this->tokens = {};
    this->pos = 0;
    this->current_token = token {END, 0};
}


