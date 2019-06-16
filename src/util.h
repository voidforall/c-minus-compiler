#ifndef C_MINUS_COMPILER_UTIL_H
#define C_MINUS_COMPILER_UTIL_H

#include "globals.h"
//#include "parser.tab.h"

Node * find_tail(Node * node);
std::string print_token(int token, const std::string & text);
void print_tree(Node * tree, int level=0);
std::string print_type(TypeKind type);
std::string print_op(OpKind op);

#endif
