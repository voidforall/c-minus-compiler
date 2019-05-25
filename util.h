#ifndef C_MINUS_COMPILER_UTIL_H
#define C_MINUS_COMPILER_UTIL_H

#include "globals.h"
//#include "parser.tab.h"

Node * find_tail(Node * node);
string print_token(int token, const string & text);

#endif
