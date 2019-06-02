//
// Created by ZBoom on 2019-06-01.
//

#include "gentiny.h"
#include "globals.h"

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
    track t;

    emitRM("LD", mp, 0, ac, "Load maximum address");
    emitRM("ST", ac, 0, ac, "Clear location 0");

    for (Node * node = tree; node != nullptr; node = node->next) {
        gentiny_code(tree, t);
    }

    emitRM("HALT", 0, 0, 0, "Halt");
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
    Node * expr = node->children[0];
    gentiny_expr((ExprNode*)expr, track);
}

void gentiny_stmt_if(IfStmtNode * node, track & track) {
    Node * cond = node->children[0];
    gentiny_expr((ExprNode*)cond, track);

    int loc1 = emitSkip(1);
    Node * stmt = node->children[1];
    gentiny_stmt((StmtNode*)stmt, track);

    if(node->children.size() == 3) {
        int loc2 = emitSkip(1);
        stmt = node->children[2];
        gentiny_stmt((StmtNode*)stmt, track);

        int current_loc = emitSkip(0);
        emitBackup(loc1);
        emitRM_Abs("JEQ", ac, loc2, "If false, jump to else part");
        emitRestore();

        emitBackup(loc2);
        emitRM_Abs("LDA", pc, current_loc, "Jump to the end");
        emitRestore();
    } else {
        int current_loc = emitSkip(0);
        emitBackup(loc1);
        emitRM_Abs("JEQ", ac, current_loc, "If false, jump to the end");
        emitRestore();
    }
}

void gentiny_stmt_iter(IterStmtNode * node, track & track) {
    Node * cond = node->children[0];

    int loc1 = emitSkip(0);
    gentiny_expr((ExprNode*)cond, track);

    int loc2 = emitSkip(1);
    Node * stmt = node->children[1];
    gentiny_stmt((StmtNode*)stmt, track);
    emitRM_Abs("LDA", pc, loc1, "Jump to while condition");

    int current_loc = emitSkip(0);
    emitBackup(loc2);
    emitRM_Abs("JEQ", ac, current_loc, "If false, end loop");
    emitRestore();
}

void gentiny_stmt_return(ReturnStmtNode * node, track & track) {
    Node * expr = node->children[0];
    gentiny_expr((ExprNode*)expr, track);
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
    string id = node->id;
    int loc = track.find_func(id);
    Node * params = node->children[0];

    for( ; params != nullptr; params = params->next) {
        gentiny_expr((ExprNode*)params, track);

    }
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
    track.current_scope = node->scope;

    int index = emitSkip(0);
    fun f(node->id, index);
    track.funs.push_back(f);

    emitRM("ST", ac, retFO, fp, "Store return address");

    for(auto x : node->children) {
        if(x != nullptr) {
            gentiny_code(x, track);
        }
    }

    track.current_scope = track.current_scope->parentScope;
}
