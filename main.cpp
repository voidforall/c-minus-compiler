#include <iostream>
#include "lexer.h"
#include "parser.tab.h"
#include "globals.h"
#include "parser.h"
#include "analyze.h"
#include "util.h"
#include "gencode.h"
#include "code.h"

using namespace std;

FILE *listing = stdout;
FILE *code = stdout;

int main(void)
{
    // fopen_s(&yyin, "../test.c", "r+");
    Node * tree = parse();

    print_tree(tree);
//    cgen(tree);
    buildTable(tree);
    typeCheck(tree);
//    int token = -1;
//    while (token != ENDFILE) {
//        token = get_token();
//    }
//    emitRO("ADD", 0, 1, 2, "comment");
    return 0;
}
