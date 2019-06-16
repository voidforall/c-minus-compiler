//
// Created by ZBoom on 2019-05-28.
//

#include "parser.tab.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "gencode.h"
#include "globals.h"

temp_manager::temp_manager(int size) {
    this->size = size;
    temp = new bool[size]();
}

void temp_manager::change_status(int index) {
    temp[index] = !temp[index];
}

int temp_manager::find_available() {
    int free = -1;
    for(int i = 0; i < size; i++) {
        if(!temp[i]) {
            free = i;
            temp[i] = !temp[i];
            break;
        }
    }
    return free;
}

pack::pack(int size, const string path, bool vis): f(path, ios::out) {
    pool = new temp_manager(size);
    t = -1;
    label = 0;
    this->vis = vis;
}

void cgen(Node * tree, string path) {
//    string path = "/Users/apple/Desktop/ZBoom/zjj/2018-2019-2nd semester/Compiler Principle/Codes/Compiler/C-minus-compiler/result.tac";
    pack param = pack(16, path, true);

    for (Node * node = tree; node != nullptr; node = node->next) {
        gen_code(node, param);
    }

    param.f.flush();
}

void gen_code(Node * node, pack & param) {
    NodeType type = node->nodetype;
    switch(type) {
        case Stmt:
//            cout << "StmtNode" << endl;
            gen_stmt((StmtNode*)node, param);
            break;
        case Decl:
//            cout << "DeclNode" << endl;
            gen_decl((DeclNode*)node, param);
            break;
        case Expr:
//            cout << "ExprNode" << endl;
            gen_expr((ExprNode*)node, param);
            break;
    }
}

void gen_decl(DeclNode * node, pack & param) {
    DeclType type = node->subtype.decl;
    switch(type) {
        case Var:
//            cout << "VarDeclNode" << endl;
            gen_decl_var((VarDeclNode*)node, param);
            break;
        case Fun:
//            cout << "FunDeclNode" << endl;
            gen_decl_fun((FunDeclNode*)node, param);
            break;
    }
}

void gen_decl_var(VarDeclNode * node, pack & param) {
    // do nothing
}

void gen_decl_fun(FunDeclNode * node, pack & param) {
    string fun_name = node->id;

    param.f << fun_name << " :\n";
    param.f << "\t" << "BeginFunc;\n";

    for(auto x : node->children) {
        if(x != nullptr) {
            gen_code(x, param);
        }
    }

    param.f << "\t" << "EndFunc;\n";

}

// ExprType : Assign, Call, Op, Const, Id
void gen_expr(ExprNode * node, pack & param) {
    ExprType type = node->subtype.expr;
    switch(type) {
        case Assign:
//            cout << "AssignExprNode" << endl;
            gen_expr_assign((AssignExprNode*)node, param);
            break;
        case Call:
//            cout << "CallExprNode" << endl;
            gen_expr_call((CallExprNode*)node, param);
            break;
        case Op:
//            cout << "OpExprNode" << endl;
            gen_expr_op((OpExprNode*)node, param);
            break;
        case Const:
//            cout << "ConstExprNode" << endl;
            gen_expr_const((ConstExprNode*)node, param);
            break;
        case Id:
//            cout << "IdExprNode" << endl;
            gen_expr_id((IdExprNode*)node, param);
            break;
    }
}

void gen_expr_assign(AssignExprNode * node, pack & param) {

    if(node->children[0]->subtype.expr == ExprType::Id && ((IdExprNode*)node->children[0])->has_index) {
        gen_expr((ExprNode*)node->children[0], param); // id
    }
    int t_0 = param.t;

    gen_expr((ExprNode*)node->children[1], param); // expr
    int t_1 = param.t;

    if(node->children[0]->subtype.expr == ExprType::Id && ((IdExprNode*)node->children[0])->has_index) {
        param.f << "\t" << "*t" << t_0 << " = ";
    } else {
        param.f << "\t" << ((IdExprNode*)node->children[0])->id << " = ";
    }

    if(node->children[1]->subtype.expr == ExprType::Id && ((IdExprNode*)node->children[1])->has_index) {
        param.f << "*t" << t_1 << ";\n";
    } else {
        param.f << "t" << t_1 << ";\n";
    }

    param.pool->change_status(t_0);
    param.pool->change_status(t_1);
}

void gen_expr_call(CallExprNode * node, pack & param) {
    Node * params = node->children[0];
    string id = node->id;
    int counter = 0;
    for(; params != nullptr; params = params->next) {
        gen_expr((ExprNode*)params, param);
        int t = param.t;
        param.f << "\t" << "PushParam ";
        if(((ExprNode*)params)->subtype.expr == ExprType::Id && ((IdExprNode*)params)->has_index) {
            param.f << "*t" << t << ";\n";
        } else {
            param.f << "t" << t << ";\n";
        }
        param.pool->change_status(t);
        counter += 1;
    }

    param.f << "\t" << "LCall " << id << ";\n";
    param.f << "\t" << "PopParams " << counter * 4 << ";\n";
}

// OpKind : Ge, Le, Gt, Lt, Eq, Ne, Plus, Minus, Times, Divide
void gen_expr_op(OpExprNode * node, pack & param) {
    gen_expr((ExprNode*)node->children[0], param);

    int t_1 = param.pool->find_available();
    int t_0 = param.t;
    if(node->children[0]->subtype.expr == ExprType::Id && ((IdExprNode*)node->children[0])->has_index) {
        param.f << "\t" << "t" << t_1 << " = *t" << t_0 << ";\n";
    } else {
        param.f << "\t" << "t" << t_1 << " = t" << t_0 << ";\n";
    }
    param.pool->change_status(t_0);

    gen_expr((ExprNode*)node->children[1], param);
    int t_2 = param.pool->find_available();
    t_0 = param.t;

    if(node->children[1]->subtype.expr == ExprType::Id && ((IdExprNode*)node->children[1])->has_index) {
        param.f << "\t" << "t" << t_2 << " = *t" << t_0 << ";\n";
    } else {
        param.f << "\t" << "t" << t_2 << " = t" << t_0 << ";\n";
    }
    param.pool->change_status(t_0);

    t_0 = param.pool->find_available();

    param.f << "\t" << "t" << t_0 << " = " << "t" << t_1;
    OpKind op = node->op;
    switch(op) {
        case Plus:
            param.f << " + ";
            break;
        case Minus:
            param.f << " - ";
            break;
        case Times:
            param.f << " * ";
            break;
        case Divide:
            param.f << " / ";
            break;
        case Ge:
            param.f << " >= ";
            break;
        case Le:
            param.f << " <= ";
            break;
        case Gt:
            param.f << " > ";
            break;
        case Lt:
            param.f << " < ";
            break;
        case Eq:
            param.f << " == ";
            break;
        case Ne:
            param.f << " != ";
            break;
        default:
            break;
    }
    param.f << "t" << t_2 << ";\n";

    param.pool->change_status(t_1);
    param.pool->change_status(t_2);
    param.t = t_0;

}

void gen_expr_const(ConstExprNode * node, pack & param) {
    int t = param.pool->find_available();

    int value = node->value;
    param.f << "\t" << "t" << t << " = " << value << ";\n";

    param.t = t;
}

// return type : &a[i]
void gen_expr_id(IdExprNode * node, pack & param) {
    string id = node->id;
    if(node->has_index) {
        gen_code(node->children[0], param);
        int t_1 = param.t;
        int t_0 = param.pool->find_available();
        if(node->children[0]->subtype.expr == ExprType::Id && ((IdExprNode*)node->children[0])->has_index) {
            param.f << "\t" << "t" << t_0 << " = *t" << t_1 << " * elem_size(" << id << ");\n";
        } else {
            param.f << "\t" << "t" << t_0 << " = t" << t_1 << " * elem_size(" << id << ");\n";
        }

        int t_2 = param.pool->find_available();
        param.f << "\t" << "t" << t_2 << " = &" << id << " + t" << t_0 << ";\n";

        param.pool->change_status(t_0);
        param.pool->change_status(t_1);
        param.t = t_2;
    } else {
        int t_0 = param.pool->find_available();
        param.f << "\t" << "t" << t_0 << " = " << id << ";\n";
        param.t = t_0;
    }
}

// StmtType : ExprStmt, If, Iter, Return, Compound
void gen_stmt(StmtNode * node, pack & param) {
    StmtType type = node->subtype.stmt;
    switch(type) {
        case ExprStmt:
//            cout << "ExprStmtNode" << endl;
            gen_stmt_expr((ExprStmtNode*)node, param);
            break;
        case If:
//            cout << "IfStmtNode" << endl;
            gen_stmt_if((IfStmtNode*)node, param);
            break;
        case Iter:
//            cout << "IterStmtNode" << endl;
            gen_stmt_iter((IterStmtNode*)node, param);
            break;
        case Return:
//            cout << "ReturnStmtNode" << endl;
            gen_stmt_return((ReturnStmtNode*)node, param);
            break;
        case Compound:
//            cout << "CompoundStmtNode" << endl;
            gen_stmt_compound((CompoundStmtNode*)node, param);
            break;
        default:
            break;
    }
}

void gen_stmt_expr(ExprStmtNode * node, pack & param) {
    Node * expr = node->children[0];
    gen_expr((ExprNode*)expr, param);
}

void gen_stmt_if(IfStmtNode * node, pack & param) {
    int label1 = param.label++;
    int label2 = param.label++;

    Node * cond = node->children[0];
    gen_expr((ExprNode*)cond, param);
    int t_0 = param.t;
    param.f << "\t" << "If_false t" << t_0 << " GOTO L" << label1 << ";\n";
    param.pool->change_status(t_0);

    Node * stmt = node->children[1];
    gen_stmt((StmtNode*)stmt, param);
    if(node->children.size() == 2) {
        param.f << "L" << label1 << ": \n";
    } else {
        param.f << "\t" << "GOTO L" << label2 << ";\n";
        param.f << "L" << label1 << ": \n";
        gen_stmt((StmtNode*)stmt, param);
        param.f << "L" << label2 << ": \n";
    }

}

void gen_stmt_iter(IterStmtNode * node, pack & param) {
    Node * cond = node->children[0];
    int label1 = param.label++;
    int label2 = param.label++;
    param.f << "L" << label1 << ": \n";
    gen_expr((ExprNode*)cond, param);

    int t_0 = param.t;
    param.f << "\t" << "If_false t" << t_0 << " GOTO L" << label2 << ";\n";
    param.pool->change_status(t_0);

    Node * stmt = node->children[1];
    gen_stmt((StmtNode*)stmt, param);
    param.f << "\t" << "GOTO L" << label1 << ";\n";
    param.f << "L" << label2 << ": \n";

}

void gen_stmt_return(ReturnStmtNode * node, pack & param) {
    Node * expr = node->children[0];
    gen_expr((ExprNode*)expr, param);
    int t_0 = param.t;

    param.f << "\t" << "Return t" << t_0 << ";\n";
    param.pool->change_status(t_0);
}

void gen_stmt_compound(CompoundStmtNode * node, pack & param) {
    Node * stmt = node->children[1];
    for(;stmt != nullptr; stmt = stmt->next) {
        gen_stmt((StmtNode*)stmt, param);
    }
}