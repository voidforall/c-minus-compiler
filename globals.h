#ifndef C_MINUS_COMPILER_GLOBALS_H
#define C_MINUS_COMPILER_GLOBALS_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstdarg>
#include <vector>
using namespace std;


// node types
typedef  enum {Stmt, Expr, Decl} NodeType;
typedef enum {Var, Fun} DeclType;
typedef enum {ExprStmt, If, Iter, Return, Compound} StmtType;
typedef enum {Assign, Call, Op, Const, Id} ExprType;

// global type specifier
typedef enum {Int, Void} TypeKind;
// global operation specifier
typedef enum {Ge, Le, Gt, Lt, Eq, Nq, Plus, Minus, Times, Divide} OpKind;


// this will be used to accept values from lex
//class Value {
//public:
//    string id;
//    // for num
//    int intval;
//    int lineno;
//
//    Value() {}
//    Value(int lineno, const string & id) : lineno(lineno), id(id) {}
//    Value(int lineno, int intval) : lineno(lineno), intval(intval) {}
//};

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
    Node * next;
    Node * parent;
    vector<Node *> children;
    int lineno;

    // methods
    Node(NodeType type) : nodetype(type) {}

    void add_child(Node * node) {
        children.push_back(node);
    }

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
    VarDeclNode(TypeKind kind, const string & id, bool is_array=false, int num=0)
            : DeclNode(Var), kind(kind), id(id), is_array(is_array), num(num) {}
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

};

class IfStmtNode : public StmtNode {
    /*
     * Two nodes:
     * - cond: ExprNode
     * - stmt: StmtNode
     */
    bool has_else = false;
    IfStmtNode(Node * cond, Node * stmt, bool has_else=false, Node * else_stmt=nullptr) : StmtNode(If) {
        this->add_child(cond);
        this->add_child(stmt);
        if (else_stmt != nullptr) {
            this->add_child(else_stmt);
        }
    }
};

class IterStmtNode : public StmtNode {
    /*
     * Two nodes:
     * - cond: ExprNode
     * - stmt: StmtNode
     */
    IterStmtNode(Node * cond, Node * stmt) : StmtNode(Iter) {
        this->add_child(cond);
        this->add_child(stmt);
    }
};

class ReturnStmtNode : public StmtNode {
    /*
     * One node:
     * - expr: ExprNode
     */
    ReturnStmtNode(Node * expr) : StmtNode(Return) {
        this->add_child(expr);
    }
};

class CompoundStmtNode : public StmtNode {
    /*
     * Two nodes:
     * - decl: a list of DeclNode
     * - stmt: a list of StmtNode
     */
    CompoundStmtNode(Node * decl, Node * stmt) : StmtNode(Compound) {
        this->add_child(decl);
        this->add_child(stmt);
    }
};

class ExprStmtNode : public StmtNode {
    /*
     * Two nodes:
     * - expr: a ExprNode. Can be empty.
     */
    ExprStmtNode(Node * expr) : StmtNode(ExprStmt) {
        if (expr != nullptr)
            this->add_child(expr);
    }
};

class AssignExprNode : public ExprNode {
    /*
     *  expr: ExprNode
     */
    string id;
    AssignExprNode(const string & id, Node * expr) : ExprNode(Assign) {
        this->id = id;
        this->add_child(expr);
    }
};

class CallExprNode : public ExprNode {
    /*
     * params: a list of Expr. Note this has to match parameters.
     */
    string id;
    CallExprNode(const string & id, Node * params) : ExprNode(Call) {
        this->id = id;
        this->add_child(params);
    }
};

class OpExprNode : public ExprNode {
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
};

class ConstExprNode : public ExprNode {
    int value;
    ConstExprNode(int value) : ExprNode(Const), value(value) {}
};

class IdExprNode : public ExprNode {
    string id;
    bool has_index = false;
    IdExprNode(const string & id, bool has_index=false, Node * index=nullptr) : ExprNode(Id), id(id) {
        this->has_index = has_index;
        if (this->has_index) {
            this->children.push_back(index);
        }
    }
};

#endif //C_MINUS_COMPILER_GLOBALS_H
