#include <iostream>
#include <cstdio>
#include "lexer.h"
#include "parser.tab.h"
#include "globals.h"
#include "parser.h"
#include "analyze.h"
#include "util.h"
#include "gencode.h"
#include "gentiny.h"
#include "code.h"

using namespace std;

FILE *listing = stdout;
FILE *code = stdout;

extern FILE * yyin;

int main(void)
{
//    yyin = fopen("test4.c", "r+");
//    if (yyin == NULL) {
//        cout << "no" << endl;
//    }
    Node * tree = parse();

//    print_tree(tree);
//    cgen(tree);
    buildTable(tree);
    typeCheck(tree);

    code = fopen("test.tm", "w");
    gentiny(tree);
    fclose(code);
//    int token = -1;
//    while (token != ENDFILE) {
//        token = get_token();
//    }
//    emitRO("ADD", 0, 1, 2, "comment");
    return 0;
}
