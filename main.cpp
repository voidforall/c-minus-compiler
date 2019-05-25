#include <iostream>
#include <unistd.h>
#include "lexer.h"
#include "parser.tab.h"
#include "globals.h"

extern "C"{
int yylex();
}

using namespace std;
int main(void)
{
    int token = -1;
    while (token != ENDFILE) {
        token = get_token();
    }
    return 0;
}
