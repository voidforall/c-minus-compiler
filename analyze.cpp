/* semantic analysis process */

#include "globals.h"
#include "symtab.h"
#include "analyze.h"

extern FILE *listing; 
static bool Error = false;
static int location = 0; // allocation of memory location

// declFunc -> true; makes the first compoundStmt in a function not nested
static bool preserveLastScope = false; // maintain nested scope (Comp)

static string analyzingFuncName;

/* Procedure traverse is a generic recursive syntax tree traversal routine:
* it applies preProc in preorder and postProc  in postorder to tree pointed to by t
* reference: Appendix A-ANALYZE.c
*/
static void traverse(Node * t, void(*preProc) (Node *), void(*postProc) (Node *)){
	/* receives preProc and postProc as two functions, e.g.
	* traverse(syntaxTree, insertNode, nullProc); traverse(syntaxTree, nullProc, checkNode);
	*/
	if (t != NULL){
		preProc(t);
		for (int i = 0; i < t->children.size(); i++) {
			traverse(t->children[i], preProc, postProc);
		}
		postProc(t);
		traverse(t->next, preProc, postProc); // next equals to sibling in tree structure
	}
}


/* nullProc is a do-nothing procedure to generate preorder-only or 
 * postorder-only traversals from traverse (maybe useless in C--)
 */
static void nullProc(Node * t){
	if (t == NULL) return;
	else return;
}


/* insertNode inserts t's identifier into the symbol table */
static void insertNode(Node * t) {
	switch (t->nodetype)
	{
	// only handles Compound - creating local scopes
	case Stmt:
		switch (t->subtype.stmt)
		{
		case Compound:
			if (preserveLastScope) // first level scope of function
				preserveLastScope = false;
			else {
				Scope scope = sc_create(analyzingFuncName);
				sc_push(scope);
				t->scope = scope;
			}
			break;
		default:
			break;
		}

	// add lineno when node is IdExprNode/CallExprNode
	case Expr:
		switch (t->subtype.expr)
		{
		case Id:
			IdExprNode *idNode = dynamic_cast<IdExprNode*>(t);
			if (st_lookup(sc_top(), idNode->id) < 0) {
				typeError(t, "undeclared variable");
			}
			else {
				/* NULL in loc field means add in lineno field */
				st_insert(idNode->id, idNode->lineno, NULL, t);
			}
			break;

		case Call:
			CallExprNode * callNode = dynamic_cast<CallExprNode*>(t);
			if (st_lookup(sc_top(), callNode->id) < 0) {
				typeError(t, "undeclared function");
			}
			else {
				st_insert(callNode->id, callNode->lineno, NULL, t);
			}
			break;
		default:
			break;
		}

	// Declaration: int a = 0; int b[10]; int gcd(int u, int v);
	case Decl:
		switch (t->subtype.decl)
		{
		case Var:
			VarDeclNode * varNode = dynamic_cast<VarDeclNode*>(t);

			if (varNode->kind == Void) {
				typeError(t, "variable can not have void data type");
				break;
			}
			if (st_lookup_nonest(sc_top(), varNode->id) < 0) {
				st_insert(varNode->id, varNode->lineno, location++ ,t);
			}
			else {
				typeError(t, "the variable has been declared in the current scope");
			}
			break;

		case Fun:
			// declaration of function will create a new scope for it
			FunDeclNode * funNode = dynamic_cast<FunDeclNode*>(t);

			if (st_lookup(sc_top(), funNode->id) >= 0) {
				typeError(t, "the function has already been declared");
				break;
			}
			/* funtion record in current symbol table but create a new scope*/
			st_insert(funNode->id, funNode->lineno, location++, t);
			sc_push(sc_create(funNode->id));
			t->scope = sc_top();
			preserveLastScope = true;
			analyzingFuncName = funNode->id;
		default:
			break;
		}
	default:
		// not likely happen unless parsing not correctly
		cout << "[Analyze.InsertNode] Error: No explicit type of the node." << endl;
		break;
	}
	return;
}


/* initSymTab initialize global symbol table,
 * inserting id input/output funtions into "global" scope table
 * int input(void){...}; void output(int x){...};
 */
static void initSymTab() {
	// create global scope
	global = sc_create("global");
	sc_push(global);


	// input & output 
	FunDeclNode *inputDecl, *outputDecl;
	// TODO: input/output not done in parser


	return;
}


/* type checking on one node */
static void checkNode(Node *t) {
	
	switch (t->nodetype)
	{
	case Stmt:
		switch (t->subtype.stmt) {
		case Compound:
			sc_pop();
			break;
		case If:
		case Iter:
		/* In if & iter stmt, cond's type cannot be void, which may be a function call return */

		{
			ExprNode *condNode = dynamic_cast<ExprNode*>(t->children[0]);
			if (condNode->kind == Void) {
				typeError(condNode, "invalid type in condition: Void");
			}
			break;
		}
		case Return:
		/* Return type should be the same as function declaration */
		{
			ExprNode *returnExpr = dynamic_cast<ExprNode*>(t->children[0]);
			BucketList funcRec = st_lookup_list(sc_top(), analyzingFuncName);

			// find the funcDeclNode in funcRec
			FunDeclNode *idDeclNode = nullptr;
			for (int i = 0; i < funcRec.size(); i++) {
				if (funcRec[i].id == analyzingFuncName) {
					idDeclNode = dynamic_cast<FunDeclNode*>(funcRec[i].node);
				}
			}

			if (idDeclNode == nullptr) { /* not likely to be called if buildTable works correctly */
				cout << "[Analyze.checkNode] Error: Function identifier cannot find in the symbol table" << endl;
				break;
			}
			if (idDeclNode->kind == Int && (returnExpr == NULL || returnExpr->kind == Void)) {
				typeError(t, "Int return value expected");
			}
			else if (idDeclNode->kind == Void &&(returnExpr->kind == Int)) {
				typeError(t, "no return value expected");
			}
			break;
		}
		default:
			break;
		}
		break;

	case Expr: /* ExprNode's attr kind have to be assigned */
		switch (t->subtype.expr) {
		case Assign:
		{
			VarDeclNode * idNode = dynamic_cast<VarDeclNode*>(t->children[0]);
			ExprNode *exprNode = dynamic_cast<ExprNode*>(t->children[1]);
			if (exprNode->kind == Void) {
				/* some callExpr may return void */
				typeError(t->children[1], "assignment with invalid type: void");
			}
			else if (idNode->is_array == true) {
				typeError(t->children[0], "assignment to an array variable");
			}
			else {
				ExprNode *exprT = dynamic_cast<ExprNode*>(t);
				exprT->kind = Int;
			}
			break;
		}

		case Call: // CallExprNode - params(nullptr/expr-expr...)
		{
			FunDeclNode * callDeclNode = nullptr;
			CallExprNode *callNode = dynamic_cast<CallExprNode*>(t);
			string funcName = callNode->id;

			BucketList l = st_lookup_list(sc_top(), funcName);
			for (int i = 0; i < l.size(); i++) {
				if (l[i].id == funcName && l[i].nodetype == Decl && l[i].subtype.decl == Fun) {
					callDeclNode = dynamic_cast<FunDeclNode*>(l[i].node);
				}
			}
			if (callDeclNode == nullptr) {
				cout << "[Analyze.checkNode] Error: Function call's identifier cannot find in the symbol table" << endl;
				break;
			}

			/* check argments type */
			ExprNode *args = dynamic_cast<ExprNode*>(t->children[0]);
			Node *params = (callDeclNode->children[0]);
			int paramNum = 0;
			/* calculate the number of parameters in function declaration*/
			while (params != NULL) {
				if (params->nodetype == Decl && params->subtype.decl == Var) {
					paramNum++;
					params = params->next;
				}
				else
					break;
			}
			
			VarDeclNode *param = dynamic_cast<VarDeclNode*>(callDeclNode->children[0]);
			/* check the parameter type */
			for (int i = 0; i < paramNum; i++) {
				if (args == NULL) {
					typeError(callDeclNode, "the number of parameters is inconsistent with declaration");
				}
				else if (args->kind == Void) {
					typeError(args, "invalid argument type: void");
				}
				else {
					args = dynamic_cast<ExprNode*>(args->next);
					param = dynamic_cast<VarDeclNode*>(param->next);
				}
			}
			if (args != NULL) {
				typeError(args, "the number of paramters is inconsistent with declaration");
			}

			break;
		}
		case Op:
		{
			/* two operands are ExprNode */
			ExprNode * op1, *op2, *exprT;
			op1 = dynamic_cast<ExprNode*>(t->children[0]);
			op2 = dynamic_cast<ExprNode*>(t->children[1]);
			exprT = dynamic_cast<ExprNode*>(t);

			if (op1->kind == Void || op2->kind == Void) {
				typeError(t->children[0], "operand's type is invalid: void");
			}
			else {
				exprT->kind = Int;
			}
			break;
		}

		case Id: /* id | id['expr'] */
		{
			IdExprNode * idExpr = dynamic_cast<IdExprNode*>(t);
			BucketList idRec = st_lookup_list(sc_top(), idExpr->id);

			// find the treeNode stored in idRec(DeclNode of the identifier)
			VarDeclNode *idDeclNode = nullptr;
			for (int i = 0; i < idRec.size(); i++) {
				if (idRec[i].id == idExpr->id) {
					idDeclNode = dynamic_cast<VarDeclNode*>(idRec[i].node);
				}
			}

			if (idDeclNode == nullptr) {
				// unlikely invoked
				cout << "[Analyze.checkNode] Error: Id cannot find in the symbol table" << endl;
				break;
			}
			if (idDeclNode->is_array) {
				ExprNode *indexNode = dynamic_cast<ExprNode*>(t->children[0]);
				if (indexNode->kind != Int) {
					typeError(indexNode, "the index of array should be Int type");
				}
				else {
					idExpr->kind = Int;
				}
			}
			else {
				idExpr->kind = idDeclNode->kind; /* identifier's kind == declartionNode's kind*/
			}
			break;
		}

		case Const:
			ExprNode * exprT = dynamic_cast<ExprNode*>(t);
			exprT->kind = Int;
			break;

		default:
			break;
		}
		break;

	/* do not need to checkNode DeclNode */
	default:
		// not likely happen unless parsing not correctly
		cout << "[Analyze.checkNode] Error: No explicit type of the node." << endl;
		break;
	}
}


/* pop out the scope saved in stack in buildTable process */
static void popScope(Node *t){
	if (t->nodetype == Stmt && t->subtype.stmt == Compound) {
		sc_pop();
	}
}


/* preorder scope maintain to checkNode in postorder traverse */
static void pushScope(Node *t) {
	/* save function name in Decl / push scope in Compound scope */
	if (t->nodetype == Decl && t->subtype.decl == Fun) {
		FunDeclNode *funNode = dynamic_cast<FunDeclNode*>(t);
		analyzingFuncName = funNode->id;
	}
	else if (t->nodetype == Stmt && t->subtype.stmt == Compound) {
		sc_push(t->scope);
	}
}


/* invoked as preorder traverse: traverse(syntaxTree, insertNode, null) */
void buildTable(Node *syntaxTree) {
	/* initialize: create global scope & input, output */
	initSymTab();
	syntaxTree->scope = sc_top(); /* program -> scope = global*/
	traverse(syntaxTree, insertNode, popScope);
	sc_pop();

	/* TraceAnalyze = False -=> only output type error 
	   TraceAnalyze = True -=> type error & symbol table */

	if (TraceAnalyze) {
		fprintf(listing, "[TraceAnalyze]: Symbol table created in analysis process: \n");
		printSymTab(listing);
	}
	return;
}


/* invoked as postorder traverse: traverse(syntaxTree, null, checkNode) */
void typeCheck(Node * syntaxTree)
{
	sc_push(global);
	traverse(syntaxTree,pushScope ,checkNode);
	sc_pop();
}


/* output the error message(lineno, error message...) */
static void typeError(Node *node, string message) {
	fprintf(listing, "Error in Line[%d]: %s\n", node->lineno, message);
	Error = true; // static error signal in analysis
}


