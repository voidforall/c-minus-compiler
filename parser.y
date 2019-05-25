%{

#include "globals.h"
#include "util.h"
#include "parser.h"

using namespace std;
static Node * parse_tree;
extern "C"
{
        int yyparse(void);
        int yylex(void);
        extern int yylineno;
}
void yyerror(char * msg);

%}

%code requires {
	#include "globals.h"
	#include <string>
}


%union{
	class Node * node;
	int intval;
	char * id;
	OpKind op;
	TypeKind type;
}

// tokens
%token '=' ';' ',' '(' ')' '[' ']' '{' '}'
%token ELSE IF RETURN WHILE
%token <type> INT VOID
%token <op> '+' '-' '*' '/' '<' '>' LE GE EQ NE
%token <id> ID
%token <intval> NUM

%type <type> type_specifier
%type <op> relop addop mulop
%type <node> program declaration_list declaration var_declaration
%type <node> fun_declaration params param_list param compound_stmt local_declarations
%type <node> stmt_list stmt expr_stmt selection_stmt iteration_stmt return_stmt
%type <node> expr var simple_expr additive_expr term factor call
%type <node> args arg_list

%left '+' '-' '*' '/' '<' '>'
%nonassoc IFX
%nonassoc ELSE

%start program

%%

program:
	declaration_list {parse_tree = $1; }
	;


declaration_list:
	declaration_list declaration {
		// here declaration returns a list
		Node * node = find_tail($1);
		node->next = $2;
		$$ = $1;
	}
	| declaration { $$ = $1; }
	;

declaration:
	var_declaration { $$ = $1;}
	| fun_declaration { $$ = $1; }
	;

var_declaration:
	type_specifier ID ';' { $$ = new VarDeclNode($1, $2); }
	| type_specifier ID '[' NUM ']' ';' { $$ = new VarDeclNode($1, $2, true, $4); }
	;

type_specifier:
	INT { $$ = Int; }
	| VOID { $$ = Void; }
	;

fun_declaration:
	type_specifier ID '(' params ')' compound_stmt {
		Node * node = new FunDeclNode($1, $2, $4, $6);
		$$ = node;
	}
	;

params:
	param_list { $$ = $1; }
	| VOID { $$ = nullptr; }
	;

param_list:
	param_list ',' param {
		Node * node = find_tail($1);
		node->next = $3;
		$$ = node;
	}
	| param { $$ = $1; }
	;

param:
	type_specifier ID { $$ = new VarDeclNode($1, $2); }
	| type_specifier ID '[' ']' { $$ = new VarDeclNode($1, $2, true); }
	;

compound_stmt:
 	'{' local_declarations stmt_list '}' { $$ = new CompoundStmtNode($2, $3); }
	;

local_declarations:
 	local_declarations var_declaration {
 	    Node * node = find_tail($1);
 	    if (node == nullptr) {
 	        $$ = $2;
 	    } else {
 	        node->next = $2;
 	        $$ = node;
 	    }
 	}
	| { $$ = nullptr; }
	;

stmt_list:
	stmt_list stmt {
		Node * node = find_tail($1);
 	    if (node == nullptr) {
 	        $$ = $2;
 	    } else {
 	        node->next = $2;
 	        $$ = node;
 	    }
	}
	| { $$ = nullptr; }
	;

stmt:
	expr_stmt { $$ = $1; }
	| compound_stmt { $$ = $1; }
	| selection_stmt { $$ = $1; }
	| iteration_stmt { $$ = $1; }
	| return_stmt { $$ = $1; }
	;

expr_stmt:
 	expr ';' { $$ = new ExprStmtNode($1); }
	| ';' { $$ = new ExprStmtNode(nullptr); }
	;

selection_stmt:
 	IF '(' expr ')' stmt %prec IFX { $$ = new IfStmtNode($3, $5); }
	| IF '(' expr ')' stmt ELSE stmt { $$ = new IfStmtNode($3, $5, true, $7); }
	;

iteration_stmt:
 	WHILE '(' expr ')' stmt { $$ = new IterStmtNode($3, $5); }
	;

return_stmt:
 	RETURN ';' { $$ = new ReturnStmtNode(nullptr); }
	| RETURN expr ';' { $$ = new ReturnStmtNode($2); }
	;

expr:
	var '=' expr { $$ = new AssignExprNode($1, $3); }
	| simple_expr { $$ = $1; }
	;

var:
	ID { $$ = new IdExprNode($1); }
	| ID '[' expr ']' { $$ = new IdExprNode($1, true, $3); }
	;

simple_expr:
	additive_expr relop additive_expr {
		$$ = new OpExprNode($2, $1, $3);
	}
	| additive_expr { $$ = $1; }
	;

relop:
	LE { $$ = Le; }
	| GE { $$ = Ge; }
	| EQ { $$ = Eq; }
	| NE { $$ = Ne; }
	| '<' { $$ = Lt; }
	| '>' { $$ = Gt; }
	;

additive_expr:
	additive_expr addop term { $$ = new OpExprNode($2, $1, $3); }
	| term { $$ = $1; }
	;

addop:
	'+' { $$ = Plus; }
	| '-' { $$ = Minus; }
	;

term:
	term mulop factor { $$ = new OpExprNode($2, $1, $3); }
	| factor {$$ = $1; }
	;

mulop:
	'*' { $$ = Times; }
	| '/' { $$ = Divide;}
	;

factor:
	'(' expr ')' { $$ = $2;}
	| var { $$ = $1; }
	| call { $$ = $1; }
	| NUM { $$ = new ConstExprNode($1); }
	;

call:
	ID '(' args ')' { $$ = new CallExprNode($1, $3);}
	;

args:
	arg_list { $$ = $1; }
	| { $$ = nullptr; }
	;

arg_list:
	arg_list ',' expr {
		Node * node = find_tail($1);
		node->next = $3;
		$$ = node;
	}
	| expr { $$ = $1; }
	;

%%

void yyerror(char * msg) {
	fprintf(stderr, "line %d: %s", yylineno, msg);
}

Node * parse() {
	yyparse();
	return parse_tree;
}
