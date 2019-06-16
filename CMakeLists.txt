cmake_minimum_required(VERSION 3.10)
project(C_minus_compiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(C_minus_compiler src/main.cpp src/globals.h src/util.cpp src/util.h src/lexer.h src/parser.h src/gencode.cpp src/gencode.h src/globals.cpp src/symtab.h src/symtab.cpp src/analyze.h src/analyze.cpp src/gentiny.cpp
        src/gentiny.h parser.tab.cpp lex.yy.cpp src/code.cpp src/code.h)
