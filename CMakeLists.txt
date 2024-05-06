cmake_minimum_required(VERSION 3.27)
project(math-interpreter)

set(CMAKE_CXX_STANDARD 17)

add_executable(math main.cpp
        src/Program.cpp
        src/Program.h
        src/lexer/lexer.cpp
        src/lexer/lexer.h
        src/parser/parser.cpp
        src/parser/parser.h
        src/io/io.cpp
        src/io/io.h
        src/ast/AstNode.h
        src/interpreter/interpreter.cpp
        src/interpreter/interpreter.h
        src/interpreter/Definition.h
        src/interpreter/ConstantDefinition.cpp
        src/interpreter/ConstantDefinition.h
        src/interpreter/ReturnValue.h
        src/interpreter/FunctionDefinition.cpp
        src/interpreter/FunctionDefinition.h
)
