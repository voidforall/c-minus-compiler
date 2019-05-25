#include <iostream>
#include <unistd.h>
#include "lexer.h"
#include "parser.tab.h"
#include "globals.h"
#include "parser.h"
#include "util.h"

extern "C"{
    int yylex();
}
using namespace std;
int main(void)
{
    Node * tree = parse();
    print_tree(tree);
//    int token = -1;
//    while (token != ENDFILE) {
//        token = get_token();
//    }
    return 0;
}
