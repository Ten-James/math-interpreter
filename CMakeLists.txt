cmake_minimum_required(VERSION 3.27)
project(oop2)

set(CMAKE_CXX_STANDARD 17)

add_executable(oop2 main.cpp
        Program.cpp
        Program.h
        lexer.cpp
        lexer.h
        parser.cpp
        parser.h
        io.cpp
        io.h
        ast/AstNode.cpp
        ast/AstNode.h
)
