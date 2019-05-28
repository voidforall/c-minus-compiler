<<<<<<< HEAD
#ifndef C_MINUS_COMPILER_GLOBALS_H
#define C_MINUS_COMPILER_GLOBALS_H

// DEBUG

const bool TraceScan = true;
const bool TraceAnalyze = true; // trace the symbol table


#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstdarg>
#include <vector>
#include <sstream>
#include <iostream>
#include "symtab.h"

#define ENDFILE 0
//#include "parser.tab.h"
using namespace std;
const int BUFSIZE = 256;

// node types
typedef  enum { Stmt, Expr, Decl } NodeType;
typedef enum { Var, Fun } DeclType;
typedef enum { ExprStmt, If, Iter, Return, Compound } StmtType;
typedef enum { Assign, Call, Op, Const, Id } ExprType;

// global type specifier
typedef enum { Int, Void, Bool } TypeKind;
// global operation specifier
typedef enum { Ge, Le, Gt, Lt, Eq, Ne, Plus, Minus, Times, Divide } OpKind;


// this will be used to accept values from lex
//class Value {
//public:
//    union {
//        string id;
//        // for num
//        int intval;
//        OpKind op;
//        TypeKind type;
//    };
//};

//class IntValue : public Value {
//    IntValue(int i) : intval(i) {}
//};
//
//class IdValue : public Value {
//    IdValue(const string & id) : id(id) {}
//};
//
//class OpValue : public Value {
//    OpValue(OpKind op) : op(op) {}
//};
//
//class TypeValue : public Value {
//    OpValue(TypeKind type) : type(type) {}
//};

extern "C" {
	int yylineno;
}

class Node {
public:
	// data members
	NodeType nodetype;
	union {
		DeclType decl;
		StmtType stmt;
		ExprType expr;
	} subtype;

	// necessary since some rules will return a list
	Node * next = nullptr;
	vector<Node *> children;
	int lineno;
	Scope scope = nullptr;

	// methods
	Node(NodeType type) : nodetype(type) {
		lineno = yylineno;
	}

	void add_child(Node * node) {
		children.push_back(node);
	}

	virtual string str();

};



class DeclNode : public Node {
public:
	DeclNode(DeclType type) : Node(Decl) {
		subtype.decl = type;
	}
};

class StmtNode : public Node {
public:
	StmtNode(StmtType type) : Node(Stmt) {
		subtype.stmt = type;
	}
};

class ExprNode : public Node {
public:
	TypeKind kind; // expression has kind which assigned in analysis
	ExprNode(ExprType type) : Node(Expr) {
		subtype.expr = type;
	}
};

class VarDeclNode : public DeclNode {
public:
	TypeKind kind;
	string id;
	bool is_array = false;
	int num = 0;
	VarDeclNode(TypeKind kind, const string & id, bool is_array = false, int num = 0)
		: DeclNode(Var), kind(kind), id(id), is_array(is_array), num(num) {}
	virtual string str();
};


class FunDeclNode : public DeclNode {
public:
	TypeKind kind;
	string id;
	// plus several parameter nodes
	FunDeclNode(TypeKind kind, const string & id, Node * param, Node * stmt)
		: DeclNode(Fun), kind(kind), id(id) {
		this->add_child(param);
		this->add_child(stmt);
	}
	virtual string str();

};

class IfStmtNode : public StmtNode {
public:
	/*
	* Two nodes:
	* - cond: ExprNode
	* - stmt: StmtNode
	*/
	bool has_else = false;
	IfStmtNode(Node * cond, Node * stmt, bool has_else = false, Node * else_stmt = nullptr) : StmtNode(If) {
		this->add_child(cond);
		this->add_child(stmt);
		if (else_stmt != nullptr) {
			this->add_child(else_stmt);
		}
	}

	virtual string str();
};

class IterStmtNode : public StmtNode {
public:
	/*
	* Two nodes:
	* - cond: ExprNode
	* - stmt: StmtNode
	*/
	IterStmtNode(Node * cond, Node * stmt) : StmtNode(Iter) {
		this->add_child(cond);
		this->add_child(stmt);
	}
	virtual string str();
};

class ReturnStmtNode : public StmtNode {
public:
	/*
	* One node:
	* - expr: ExprNode
	*/
	ReturnStmtNode(Node * expr) : StmtNode(Return) {
		this->add_child(expr);
	}
	virtual string str();
};

class CompoundStmtNode : public StmtNode {
public:
	/*
	* Two nodes:
	* - decl: a list of DeclNode
	* - stmt: a list of StmtNode
	*/
	CompoundStmtNode(Node * decl, Node * stmt) : StmtNode(Compound) {
		this->add_child(decl);
		this->add_child(stmt);
	}

	virtual string str();
};

class ExprStmtNode : public StmtNode {
public:
	/*
	* Two nodes:
	* - expr: a ExprNode. Can be empty.
	*/
	ExprStmtNode(Node * expr) : StmtNode(ExprStmt) {
		if (expr != nullptr)
			this->add_child(expr);
	}

	virtual string str();
};

class AssignExprNode : public ExprNode {
public:
	/*
	*  id: IdExprNode
	*  expr: ExprNode
	*/
	AssignExprNode(Node * id, Node * expr) : ExprNode(Assign) {
		this->add_child(id);
		this->add_child(expr);
	}

	virtual string str();
};

class CallExprNode : public ExprNode {
public:
	/*
	* params: a list of Expr. Note this has to match parameters.
	*/
	string id;
	CallExprNode(const string & id, Node * params) : ExprNode(Call) {
		this->id = id;
		this->add_child(params);
	}

	virtual string str();
};

class OpExprNode : public ExprNode {
public:
	/*
	* exp1: ExprNode
	* exp2: ExprNode
	*/
	OpKind op;
	OpExprNode(OpKind op, Node * exp1, Node * exp2) : ExprNode(Op) {
		this->op = op;
		this->add_child(exp1);
		this->add_child(exp2);
	}

	virtual string str();
};

class ConstExprNode : public ExprNode {
public:
	int value;
	ConstExprNode(int value) : ExprNode(Const), value(value) {}
	virtual string str();
};

class IdExprNode : public ExprNode {
public:
	string id;
	bool has_index = false;
	IdExprNode(const string & id, bool has_index = false, Node * index = nullptr) : ExprNode(Id), id(id) {
		this->has_index = has_index;
		if (this->has_index) {
			this->children.push_back(index);
		}
	}

	virtual string str();
};

#endif //C_MINUS_COMPILER_GLOBALS_H
=======
#ifndef C_MINUS_COMPILER_GLOBALS_H
#define C_MINUS_COMPILER_GLOBALS_H

// DEBUG

const bool TraceScan = true;
const bool TraceAnalyze = true; // trace the symbol table


#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstdarg>
#include <vector>
#include <sstream>
#include <iostream>
#include "symtab.h"

#define ENDFILE 0
//#include "parser.tab.h"
using namespace std;
const int BUFSIZE = 256;

// node types
typedef  enum { Stmt, Expr, Decl } NodeType;
typedef enum { Var, Fun } DeclType;
typedef enum { ExprStmt, If, Iter, Return, Compound } StmtType;
typedef enum { Assign, Call, Op, Const, Id } ExprType;

// global type specifier
typedef enum { Int, Void, Bool } TypeKind;
// global operation specifier
typedef enum { Ge, Le, Gt, Lt, Eq, Ne, Plus, Minus, Times, Divide } OpKind;


// this will be used to accept values from lex
//class Value {
//public:
//    union {
//        string id;
//        // for num
//        int intval;
//        OpKind op;
//        TypeKind type;
//    };
//};

//class IntValue : public Value {
//    IntValue(int i) : intval(i) {}
//};
//
//class IdValue : public Value {
//    IdValue(const string & id) : id(id) {}
//};
//
//class OpValue : public Value {
//    OpValue(OpKind op) : op(op) {}
//};
//
//class TypeValue : public Value {
//    OpValue(TypeKind type) : type(type) {}
//};

extern "C" {
	int yylineno;
}

class Node {
public:
	// data members
	NodeType nodetype;
	union {
		DeclType decl;
		StmtType stmt;
		ExprType expr;
	} subtype;

	// necessary since some rules will return a list
	Node * next = nullptr;
	vector<Node *> children;
	int lineno;
	Scope scope = nullptr;

	// methods
	Node(NodeType type) : nodetype(type) {
		lineno = yylineno;
	}

	void add_child(Node * node) {
		children.push_back(node);
	}

	virtual string str();

};



class DeclNode : public Node {
public:
	DeclNode(DeclType type) : Node(Decl) {
		subtype.decl = type;
	}
};

class StmtNode : public Node {
public:
	StmtNode(StmtType type) : Node(Stmt) {
		subtype.stmt = type;
	}
};

class ExprNode : public Node {
public:
	TypeKind kind; // expression has kind which assigned in analysis
	ExprNode(ExprType type) : Node(Expr) {
		subtype.expr = type;
	}
};

class VarDeclNode : public DeclNode {
public:
	TypeKind kind;
	string id;
	bool is_array = false;
	int num = 0;
	VarDeclNode(TypeKind kind, const string & id, bool is_array = false, int num = 0)
		: DeclNode(Var), kind(kind), id(id), is_array(is_array), num(num) {}
	virtual string str();
};


class FunDeclNode : public DeclNode {
public:
	TypeKind kind;
	string id;
	// plus several parameter nodes
	FunDeclNode(TypeKind kind, const string & id, Node * param, Node * stmt)
		: DeclNode(Fun), kind(kind), id(id) {
		this->add_child(param);
		this->add_child(stmt);
	}
	virtual string str();

};

class IfStmtNode : public StmtNode {
public:
	/*
	* Two nodes:
	* - cond: ExprNode
	* - stmt: StmtNode
	*/
	bool has_else = false;
	IfStmtNode(Node * cond, Node * stmt, bool has_else = false, Node * else_stmt = nullptr) : StmtNode(If) {
		this->add_child(cond);
		this->add_child(stmt);
		if (else_stmt != nullptr) {
			this->add_child(else_stmt);
		}
	}

	virtual string str();
};

class IterStmtNode : public StmtNode {
public:
	/*
	* Two nodes:
	* - cond: ExprNode
	* - stmt: StmtNode
	*/
	IterStmtNode(Node * cond, Node * stmt) : StmtNode(Iter) {
		this->add_child(cond);
		this->add_child(stmt);
	}
	virtual string str();
};

class ReturnStmtNode : public StmtNode {
public:
	/*
	* One node:
	* - expr: ExprNode
	*/
	ReturnStmtNode(Node * expr) : StmtNode(Return) {
		this->add_child(expr);
	}
	virtual string str();
};

class CompoundStmtNode : public StmtNode {
public:
	/*
	* Two nodes:
	* - decl: a list of DeclNode
	* - stmt: a list of StmtNode
	*/
	CompoundStmtNode(Node * decl, Node * stmt) : StmtNode(Compound) {
		this->add_child(decl);
		this->add_child(stmt);
	}

	virtual string str();
};

class ExprStmtNode : public StmtNode {
public:
	/*
	* Two nodes:
	* - expr: a ExprNode. Can be empty.
	*/
	ExprStmtNode(Node * expr) : StmtNode(ExprStmt) {
		if (expr != nullptr)
			this->add_child(expr);
	}

	virtual string str();
};

class AssignExprNode : public ExprNode {
public:
	/*
	*  id: IdExprNode
	*  expr: ExprNode
	*/
	AssignExprNode(Node * id, Node * expr) : ExprNode(Assign) {
		this->add_child(id);
		this->add_child(expr);
	}

	virtual string str();
};

class CallExprNode : public ExprNode {
public:
	/*
	* params: a list of Expr. Note this has to match parameters.
	*/
	string id;
	CallExprNode(const string & id, Node * params) : ExprNode(Call) {
		this->id = id;
		this->add_child(params);
	}

	virtual string str();
};

class OpExprNode : public ExprNode {
public:
	/*
	* exp1: ExprNode
	* exp2: ExprNode
	*/
	OpKind op;
	OpExprNode(OpKind op, Node * exp1, Node * exp2) : ExprNode(Op) {
		this->op = op;
		this->add_child(exp1);
		this->add_child(exp2);
	}

	virtual string str();
};

class ConstExprNode : public ExprNode {
public:
	int value;
	ConstExprNode(int value) : ExprNode(Const), value(value) {}
	virtual string str();
};

class IdExprNode : public ExprNode {
public:
	string id;
	bool has_index = false;
	IdExprNode(const string & id, bool has_index = false, Node * index = nullptr) : ExprNode(Id), id(id) {
		this->has_index = has_index;
		if (this->has_index) {
			this->children.push_back(index);
		}
	}

	virtual string str();
};

#endif //C_MINUS_COMPILER_GLOBALS_H
>>>>>>> c710f588a2ef7d0082bb3bf7ee1a56db3f67639c
