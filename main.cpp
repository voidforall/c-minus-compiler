#include <iostream>
#include <unistd.h>
#include "lexer.h"
#include "parser.tab.h"
#include "globals.h"
#include "parser.h"
#include "analyze.h"
#include "util.h"

extern "C"{
    int yylex();
}
using namespace std;

FILE *listing = stdout;

int main(void)
{
    Node * tree = parse();

    print_tree(tree);    buildTable(tree);
//    int token = -1;
//    while (token != ENDFILE) {
//        token = get_token();
//    }
    return 0;
}
