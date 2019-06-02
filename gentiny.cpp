//
// Created by ZBoom on 2019-06-01.
//

#include "gentiny.h"

fun::fun(string fun_name, int index) {
    this->fun_name = fun_name;
    this->index = index;
}

void track::add_func(string id, int index) {
    fun f(id, index);
    funs.push_back(f);
}

int track::find_func(string id) {
    int index = NOT_FOUND;
    for (int i = 0; i < funs.size(); i++) {
        if (funs[i].fun_name == id) {
            index = i;
            break;
        }
    }
    return index;
}

void gentiny(Node * tree) {
    string path = "/Users/apple/Desktop/ZBoom/zjj/2018-2019-2nd semester/Compiler Principle/Codes/Compiler/C-minus-compiler/result.tiny";
    track t;

    for (Node * node = tree; node != nullptr; node = node->next) {
        gentiny_code(tree, t);
    }
}

void gentiny_code(Node * node, track & track) {
    NodeType type = node->nodetype;
    switch(type) {
        case Stmt:
            gentiny_stmt((StmtNode*)node, track);
            break;
        case Decl:
            gentiny_decl((DeclNode*)node, track);
            break;
        case Expr:
            gentiny_expr((ExprNode*)node, track);
            break;
    }
}

void gentiny_stmt(StmtNode * node, track & track) {
    StmtType type = node->subtype.stmt;
    switch(type) {
        case ExprStmt:
            gentiny_stmt_expr((ExprStmtNode*)node, track);
            break;
        case If:
            gentiny_stmt_if((IfStmtNode*)node, track);
            break;
        case Iter:
            gentiny_stmt_iter((IterStmtNode*)node, track);
            break;
        case Return:
            gentiny_stmt_return((ReturnStmtNode*)node, track);
            break;
        case Compound:
            gentiny_stmt_compound((CompoundStmtNode*)node, track);
            break;
        default:
            break;
    }
}

void gentiny_stmt_expr(ExprStmtNode * node, track & track) {

}

void gentiny_stmt_if(IfStmtNode * node, track & track) {

}

void gentiny_stmt_iter(IterStmtNode * node, track & track) {

}

void gentiny_stmt_return(ReturnStmtNode * node, track & track) {

}

void gentiny_stmt_compound(CompoundStmtNode * node, track & track) {

}

void gentiny_expr(ExprNode * node, track & track) {
    ExprType type = node->subtype.expr;
    switch(type) {
        case Assign:
            gentiny_expr_assign((AssignExprNode*)node, track);
            break;
        case Call:
            gentiny_expr_call((CallExprNode*)node, track);
            break;
        case Op:
            gentiny_expr_op((OpExprNode*)node, track);
            break;
        case Const:
            gentiny_expr_const((ConstExprNode*)node, track);
            break;
        case Id:
            gentiny_expr_id((IdExprNode*)node, track);
            break;
    }
}

void gentiny_expr_assign(AssignExprNode * node, track & track) {

}

void gentiny_expr_call(CallExprNode * node, track & track) {

}

void gentiny_expr_op(OpExprNode * node, track & track) {

}

void gentiny_expr_const(ConstExprNode * node, track & track) {

}

void gentiny_expr_id(IdExprNode * node, track & track) {

}

void gentiny_decl(DeclNode * node, track & track) {
    DeclType type = node->subtype.decl;
    switch(type) {
        case Var:
            gentiny_decl_var((VarDeclNode*)node, track);
            break;
        case Fun:
            gentiny_decl_fun((FunDeclNode*)node, track);
            break;
    }
}

void gentiny_decl_var(VarDeclNode * node, track & track) {

}

void gentiny_decl_fun(FunDeclNode * node, track & track) {

}
