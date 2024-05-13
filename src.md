### Program.h
```cpp
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
```

### Definition.h
```cpp
//
// Created by Jakub Indrák on 06.05.2024.
//

#ifndef DEFINITION_H
#define DEFINITION_H
#include <utility>

#include "ReturnValue.h"
#include "../ast/AstNode.h"


class Definition {
public:
    std::string name;
    AstNode* value;
    Definition(std::string name, AstNode* value) : name{std::move(name)}, value{value} {};
    virtual ReturnValue visit() = 0;
    virtual ~Definition() = default;
};



#endif //DEFINITION_H
```

### Interpreter.h
```cpp
//
// Created by Jakub Indrák on 30.04.2024.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "ReturnValue.h"
#include "Definition.h"
#include "../ast/AstNode.h"
#include <vector>




class Interpreter {
private:
    static std::vector<Definition*> definitions;
    static ReturnValue visit(AstNode* node, std::vector<Definition*> local_scope = {});
public:
    static ReturnValue interpret(AstNode* node, std::vector<Definition*> local_scope = {});
    static ReturnValue add_definition(AstDefinition* definition);
    static ReturnValue add_definition(AstFunDefinition* definition);
};



#endif //INTERPRETER_H
```

### ReturnValue.h
```cpp
//
// Created by Jakub Indrák on 06.05.2024.
//

#ifndef RETURNVALUE_H
#define RETURNVALUE_H


struct ReturnValue {
    bool isReturn;
    double value;
};

#endif //RETURNVALUE_H
```

### FunctionDefinition.h
```cpp
//
// Created by Jakub Indrák on 06.05.2024.
//

#ifndef FUNCTIONDEFINITION_H
#define FUNCTIONDEFINITION_H
#include "Definition.h"
#include <utility>
#include <vector>


class FunctionDefinition: public Definition {
private:
    std::vector<std::string> args;
public:
    ReturnValue visit() override;
    ReturnValue visit(const AstFunction* function);
    FunctionDefinition(std::string name, std::vector<std::string> args, AstNode* value): Definition(std::move(name), value), args(std::move(args)) {}
    std::vector<std::string>& get_args() { return args; }

};



#endif //FUNCTIONDEFINITION_H
```

### ConstantDefinition.h
```cpp
//
// Created by Jakub Indrák on 06.05.2024.
//

#ifndef CONSTANTDEFINITION_H
#define CONSTANTDEFINITION_H
#include "Definition.h"

#include <utility>


class ConstantDefinition : public Definition {
public:
    ReturnValue visit() override;
    ConstantDefinition(std::string name, AstNode* value) : Definition{std::move(name), value} {}
};



#endif //CONSTANTDEFINITION_H
```

### lexer.h
```cpp
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
```

### io.h
```cpp
//
// Created by james on 3/27/24.
//

#ifndef OOP2_IO_H
#define OOP2_IO_H
#include "../lexer/lexer.h"
#include "../ast/AstNode.h"
#include "../interpreter/Interpreter.h"

class io {
public:
    void printAst(AstNode* node);
    std::string readText();
    void printResult(ReturnValue result);
    void printError(const char* error);

};


#endif //OOP2_IO_H
```

### parser.h
```cpp
//
// Created by james on 3/27/24.
//

#ifndef OOP2_PARSER_H
#define OOP2_PARSER_H
#include "../lexer/lexer.h"
#include "../ast/AstNode.h"
#include <vector>

/*
 *
 * GRAMATIKA
 *
 * expr -> term ((PLUS | MINUS) term)*
 * term -> factor ((MUL | DIV) factor)*
 * factor
 *    -> MINUS factor
 *    -> NUM
 *    -> LPAREN expr RPAREN
 *    -> ID
 *
 * definition
 *    -> ID EQ expr
 *    -> ID LPAREN ID (COMMA ID)* RPAREN EQ expr
 *
 * line -> expr | definition
 *
 */


class parser {
    std::vector<token> tokens;
    int pos = 0;
    token current_token;
    void error();
    void error(std::string message);
    void advance();
    void eat(token_type type);
    AstNode* factor();
    AstNode* term();
    AstNode* definition();
    AstNode* line();
    AstNode* expr();
public:
    parser();
    void reset(std::vector<token> tokens);
    AstNode* parse();

};


#endif //OOP2_PARSER_H
```

### AstNode.h
```cpp
//
// Created by james on 3/27/24.
//

#ifndef OOP2_ASTNODE_H
#define OOP2_ASTNODE_H

#include <vector>
#include <string>
#include <iostream>
#include <utility>

enum AstType {
    OPERATOR,
    NUMBER,
    UNARY,
    DEFINITION,
    FUN_DEFINITION,
    VARIABLE,
    FUNCTION
};


class AstNode {
    public:
    virtual AstType get_type() const = 0;
    virtual void print(std::string offset) = 0;
    virtual ~AstNode() = default;
    virtual AstNode* copy() = 0;

};

class AstOperator : public AstNode {
    char op;
    AstNode *left;
    AstNode *right;
public:
    AstType get_type() const override {
        return OPERATOR;
    }
    AstOperator(char op, AstNode *left, AstNode *right) : op(op), left(left), right(right) {}
    AstNode* copy() override
    {
        return new AstOperator(op, left->copy(), right->copy());
    }
    ~AstOperator() override {
        delete left;
        delete right;
    }
    void print(std::string offset) override {
        std::cout << offset;
        std::cout << op;
        std::cout << std::endl;
        std::cout << offset;
        left->print(offset + " ");
        std::cout << std::endl;
        std::cout << offset;
        right->print(offset + " ");
    }
    char get_op() const {
        return op;
    }
    AstNode* get_left() const
    {
        return left;
    }
    AstNode* get_right() const
    {
        return right;
    }
};

class AstNumber : public AstNode {
    double value;
public:
    AstType get_type() const override {
        return NUMBER;
    }
    explicit AstNumber(double value) : value(value) {}
    AstNode* copy() override
    {
        return new AstNumber(value);
    }
    void print(std::string offset) {
        std::cout << offset;
        std::cout << value;
    }
    double get_value() const {
        return value;
    }
};

class AstUnary : public AstNode {
    char op;
    AstNode *expr;
public:
    AstType get_type() const override {
        return UNARY;
    }
    AstUnary(char op, AstNode *expr) : op(op), expr(expr) {}
    AstNode* copy() override
    {
        return new AstUnary(op, expr->copy());
    }
    ~AstUnary() override
    {
        delete expr;
    }
    void print(std::string offset) override
    {
        std::cout << offset;
        std::cout << "Unary: ";
        std::cout << op;
        std::cout << std::endl;
        std::cout << offset;
        expr->print(offset + " ");
    }
    char get_op() const {
        return op;
    }
    AstNode* get_expr() const {
        return expr;
    }
};

class AstDefinition : public AstNode {
    std::string name;
    AstNode *value;
public:
    AstType get_type() const override {
        return DEFINITION;
    }
    AstDefinition(std::string name, AstNode *value) : name(std::move(name)), value(value) {}
    AstNode* copy() override
    {
        return new AstDefinition(name, value->copy());
    }
    ~AstDefinition() override {
        delete value;
    }
    void print(std::string offset) override {
        std::cout << offset;
        std::cout << "Constant: ";
        std::cout << name;
        std::cout << std::endl;
        std::cout << offset;
        value->print(offset + " ");
    }
    std::string get_name() const {
        return name;
    }
    AstNode* get_value() const {
        return value;
    }
    void undefine()
    {
        value = 0;
    }
};

class AstFunDefinition : public AstDefinition {
    std::vector<std::string> args;
public:
    AstType get_type() const override {
        return FUN_DEFINITION;
    }
    AstFunDefinition(std::string name, AstNode *value, std::vector<std::string> args) : AstDefinition(std::move(name), value), args(std::move(args)) {}
    AstNode* copy() override
    {
        return new AstFunDefinition(get_name(), get_value()->copy(), args);
    }
    void print(std::string offset) override {
        std::cout << offset;
        std::cout << "Function: ";
        std::cout << get_name();
        std::cout << std::endl;
        std::cout << offset;
        std::cout << "Arguments: ";
        for (const auto &arg : args) {
            std::cout << arg << " ";
        }
        std::cout << std::endl;
        AstDefinition::print(offset);
    }
    const std::vector<std::string>& get_args() const {
        return args;
    }
};




class AstVariable : public AstNode {
    std::string name;
public:
    AstType get_type() const override {
        return VARIABLE;
    }
    AstVariable(std::string name) : name(std::move(name)) {}
    AstNode* copy() override
    {
        return new AstVariable(name);
    }
    void print(std::string offset) override {
        std::cout << offset;
        std::cout << "Variable: ";
        std::cout << name;
    }
    std::string get_name() const {
        return name;
    }
};

class AstFunction : public AstNode {
    std::string name;
    std::vector<AstNode*> args;
public:
    AstType get_type() const override {
        return FUNCTION;
    }
    AstFunction(std::string name, std::vector<AstNode*> args) : name(std::move(name)), args(std::move(args)) {}
    AstNode* copy() override
    {
        std::vector<AstNode*> new_args = {};
        for (const auto arg : args)
        {
            auto new_arg = arg->copy();
            new_args.push_back(new_arg);
        }
        return new AstFunction(name, new_args);
    }
    ~AstFunction() override {
        for (auto arg : args) {
            delete arg;
        }
    }
    void print(std::string offset) override {
        std::cout << offset;
        std::cout << "Function: ";
        std::cout << name;
        std::cout << std::endl;
        std::cout << offset;
        std::cout << "Arguments: ";
        for (const auto &arg : args) {
            arg->print(offset + " ");
        }
    }
    const std::string& get_name() const {
        return name;
    }
    const std::vector<AstNode*>& get_args() const {
        return args;
    }
};


#endif //OOP2_ASTNODE_H
```

