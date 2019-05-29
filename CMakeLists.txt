cmake_minimum_required(VERSION 3.10)
project(C_minus_compiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(C_minus_compiler main.cpp globals.h util.cpp util.h lexer.h parser.h gencode.cpp gencode.h globals.cpp symtab.h symtab.cpp analyze.h analyze.cpp)
