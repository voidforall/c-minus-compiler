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

extern bool Error;
const bool GEN_INTERMEDIATE = true;

FILE *listing = stdout;
FILE *code = stdout;

extern FILE * yyin;

int main(int argc, char * argv[])
{
    if (argc != 3) {
        cout << "Usage: cminus [INPUT] [OUTPUT]";
        exit(0);
    }
    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        printf("File %s does not exists.\n", argv[1]);
        exit(0);
    }
    Node * tree = parse();

    buildTable(tree);
    typeCheck(tree);

    if (Error) {
        exit(0);
    }

    code = fopen(argv[2], "w");
    if (code == NULL) {
        printf("Cannot create file %s.\n", argv[2]);
        exit(0);
    }
    // generate tiny code
    gentiny(tree);
    fclose(code);

    // generate intermediate code
    if (GEN_INTERMEDIATE)
        cgen(tree, "./result.tac");

    cout << "compilation completed\n";
    return 0;
}
