%{
#include "globals.h"
#include "parser.tab.h"
#include <cstdio>
#include "lexer.h"
#include <iostream>
#include "util.h"

extern "C" {
int yylex(void);
}
void yyerror(char * msg);
%}

%option yylineno
%x C_COMMENT

digit [0-9]
letter [a-zA-Z]
id {letter}+
num {digit}+
whitespace [ \t\n]+

%%
"else"      { return ELSE; }
"if"        { return IF; }
"return"    { return RETURN;}
"void"		{ yylval.type = Void; return VOID;}
"int"       { yylval.type = Int; return INT; }
"while"		{ return WHILE;}
"+"         { yylval.op = Plus; return '+';}
"-"         { yylval.op = Minus; return '-';}
"*"         { yylval.op = Times; return '*';}
"/"         { yylval.op = Divide; return '/';}
"<"         { yylval.op = Lt; return '<';}
"<="		{ yylval.op = Le; return LE; }
">"         { yylval.op = Gt; return '>'; }
">="        { yylval.op = Ge; return GE; }
"=="        { yylval.op = Eq; return EQ; }
"!="        { yylval.op = Ne; return NE; }
"="         { return '='; }
";"         { return ';'; }
","         { return ','; }
"("         { return '('; }
")"         { return ')'; }
"["         { return '['; }
"]"         { return ']'; }
"{"         { return '{'; }
"}"         { return '}'; }

{id}    {
	char * text = new char[BUFSIZE];
	strcpy(text, yytext);
	yylval.id = text;
	return ID;
}
{num}   { yylval.intval = atoi(yytext); return NUM; }
{whitespace}    ;
"/*"            { BEGIN(C_COMMENT); }
<C_COMMENT>"*/" { BEGIN(INITIAL); }
<C_COMMENT>.    { }
<C_COMMENT>\n   { }
. yyerror("invalid character\n");

%%
int yywrap()
{
		return 1;
}

int get_token() {
	int token = yylex();
	if (TraceScan)
		printf("%d: %s\n", yylineno, print_token(token, yytext).c_str());
	return token;
}

