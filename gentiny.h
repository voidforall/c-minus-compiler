//
// Created by ZBoom on 2019-06-01.
//

#ifndef C_MINUS_COMPILER_GENTINY_H
#define C_MINUS_COMPILER_GENTINY_H

#include "globals.h"

#define NOT_FOUND -1

class fun {
public:
    string fun_name;
    int index;
    fun(string fun_name, int index);
};

class track {
public:
    Scope current_scope;
    vector<fun> funs;
    void add_func(string id, int index);
    int find_func(string id);
};

void gentiny(Node * tree);
void gentiny_code(Node * tree, track & track);

// DeclType : Var, Fun
void gentiny_decl(DeclNode * tree, track & track);
void gentiny_decl_var(VarDeclNode * node, track & track);
void gentiny_decl_fun(FunDeclNode * node, track & track);

// ExprType : Assign, Call, Op, Const, Id
void gentiny_expr(ExprNode * tree, track & track);
void gentiny_expr_assign(AssignExprNode * node, track & track);
void gentiny_expr_call(CallExprNode * node, track & track);
void gentiny_expr_op(OpExprNode * node, track & track);
void gentiny_expr_const(ConstExprNode * node, track & track);
void gentiny_expr_id(IdExprNode * node, track & track);

// StmtType : ExprStmt, If, Iter, Return, Compound
void gentiny_stmt(StmtNode * tree, track & track);
void gentiny_stmt_expr(ExprStmtNode * node, track & track);
void gentiny_stmt_if(IfStmtNode * node, track & track);
void gentiny_stmt_iter(IterStmtNode * node, track & track);
void gentiny_stmt_return(ReturnStmtNode * node, track & track);
void gentiny_stmt_compound(CompoundStmtNode * node, track & track);

#endif //C_MINUS_COMPILER_GENTINY_H
