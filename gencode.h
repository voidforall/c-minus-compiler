//
// Created by ZBoom on 2019-05-28.
//

#ifndef C_MINUS_COMPILER_GENCODE_H
#define C_MINUS_COMPILER_GENCODE_H

#include "globals.h"

class temp_manager {
private:
    bool * temp;
    int size;
public:
    temp_manager(int size);
    void change_status(int index);
    int find_available();
};

class pack {
public:
    temp_manager * pool;
    ofstream f;
    int t;
    int label;
    bool vis;
    pack(int size, string path, bool vis);
};

void cgen(Node * tree);
void gen_code(Node * tree, pack & param);

// DeclType : Var, Fun
void gen_decl(DeclNode * tree, pack & param);
void gen_decl_var(VarDeclNode * node, pack & param);
void gen_decl_fun(FunDeclNode * node, pack & param);

// ExprType : Assign, Call, Op, Const, Id
void gen_expr(ExprNode * tree, pack & param);
void gen_expr_assign(AssignExprNode * node, pack & param);
void gen_expr_call(CallExprNode * node, pack & param);
void gen_expr_op(OpExprNode * node, pack & param);
void gen_expr_const(ConstExprNode * node, pack & param);
void gen_expr_id(IdExprNode * node, pack & param);

// StmtType : ExprStmt, If, Iter, Return, Compound
void gen_stmt(StmtNode * tree, pack & param);
void gen_stmt_expr(ExprStmtNode * node, pack & param);
void gen_stmt_if(IfStmtNode * node, pack & param);
void gen_stmt_iter(IterStmtNode * node, pack & param);
void gen_stmt_return(ReturnStmtNode * node, pack & param);
void gen_stmt_compound(CompoundStmtNode * node, pack & param);

#endif //C_MINUS_COMPILER_GENCODE_H
