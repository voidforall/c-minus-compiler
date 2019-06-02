//
// Created by ZBoom on 2019-06-01.
//

#include "globals.h"
#include "gentiny.h"
#include "code.h"
#include <cstdlib>

char buffer[1024];
const int ofpFO = 0;
const int retFO = -1;
const int  initFO = -2;

extern Scope global;

// this serves as a stack pointer maintained by the compiler
static int frame_offset = initFO;


static int param_offset(VarDeclNode * param_list) {
    int offset = 0;
    for (Node * node = param_list; node != nullptr; node = node->next) {
        offset += 1;
    }

    return offset;
}

static void gen_input(track & track) {
    // copied from gen_fun
    track.add_func("input", emitSkip(0));

    emitRM("ST", ac, retFO, fp, "save return address in fp + retFO");
    emitRO("IN", ac, 0, 0, "read input");
    emitRM("LD", pc, retFO, fp, "return to caller");
}

static void gen_output(track & track) {
    // copied from gen_fun
    track.add_func("output", emitSkip(0));

    emitRM("ST", ac, retFO, fp, "save return address in fp + retFO");
    // save parameter to a register
    emitRM("LD", ac, initFO, fp, "get x for output");
    emitRO("OUT", ac, 0, 0, "output x");
    emitRM("LD", pc, retFO, fp, "return to caller");
}

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
            index = funs[i].index;
            break;
        }
    }
    return index;
}

void gentiny(Node * tree) {
    track t;

    emitComment("C-- Compilation to TM code");
    emitComment("Standard prelude:");
    emitRM("LD", mp, 0, ac, "load maxaddress from location 0");
    emitRM("ST", ac, 0, ac, "clear loation 0");
    // skip three command. These are:
    // set fp
    // set return address to halt
    // jump to main
    int saved_loc = emitSkip(3);
    emitComment("End of standard prelude:");
    emitComment("Begin generating built-ins");
    emitComment("Generate built-in input");
    gen_input(t);
    emitComment("Generate built-in output");
    gen_output(t);
    emitComment("End generating built-in");

    // we assume that the global area is the first frame. Each declaration occupies one slot
    int init_fp = 0;
    for (Node * node = tree; node != nullptr; node = node->next) {
        gentiny_code(node, t);
        init_fp--;
    }
    emitComment("End of execution");

    // back patch
    int halt_loc = emitSkip(0);
    emitBackup(saved_loc);
    // set frame pointer
    emitRM("LDA", fp, init_fp, mp, "load initial frame pointer");
    // set return address to halt
    emitRM_Abs("LDA", ac, halt_loc, "set return address to halt");
    // perform jump
    emitRM_Abs("JEQ", gp, t.find_func("main"), "jump to main");
    // go back to produce halt
    emitRestore();
    emitRO("HALT", 0, 0, 0, "");
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
    if (node->children[0] != nullptr) {
        gentiny_expr(dynamic_cast<ExprNode *>(node->children[0]), track);
    }
}

void gentiny_stmt_if(IfStmtNode * node, track & track) {

}

void gentiny_stmt_iter(IterStmtNode * node, track & track) {

}

void gentiny_stmt_return(ReturnStmtNode * node, track & track) {

}

void gentiny_stmt_compound(CompoundStmtNode * node, track & track) {

    if (node->scope != nullptr) {
        // for function scope, this can be null
        track.current_scope = node->scope;
    }

    for (Node * decl = node->children[0]; decl != nullptr; decl = decl->next) {
        gentiny_code(decl, track);
    }

    for (Node * stmt = node->children[1]; stmt != nullptr; stmt = stmt->next) {
        gentiny_code(stmt, track);
    }

    if (node->scope != nullptr) {
        // restore scope
        track.current_scope = node->scope->parentScope;
    }
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
    if (TraceCode) {
        sprintf(buffer, "-> Calling (%s)", node->id.c_str());
        emitComment(buffer);
    }

    // the slot is for old frame pointer. fp + frame_offset will be the new frame pointer
    frame_offset--;

    // frame offset is the current stack pointer
    // compute arguments
    int param_offset = 0;
    for (Node * param = node->children[0]; param != nullptr; param = param->next) {
        // param is a exp node
        gentiny_code(param, track);
        // after this, result will be stored in ac. Store this
        sprintf(buffer, "store parameter %s", param_offset);
        emitRM("ST", ac, frame_offset + initFO + param_offset, fp, buffer);
    }

    // store old frame pointer
    emitRM("ST", fp, frame_offset + ofpFO, fp, "store old frame pointer");
    // push new frame
    emitRM("LDA", fp, frame_offset, fp, "push new frame");
    // save return in ac
    emitRM("LDA", ac, 1, pc, "save return address in ac");
    // jump. This uses the global address of the function
    emitRM_Abs("LDA", pc, track.find_func(node->id), "jump to the function");

    // after call done, pop current frame. At this point, fp is the new fp
    emitRM("LD", fp, ofpFO, fp, "restore frame pointer");

    // because no real space is used, we change this back
    frame_offset++;
}

void gentiny_expr_op(OpExprNode * node, track & track) {

}

void gentiny_expr_const(ConstExprNode * node, track & track) {
    emitRO("LDC", ac, node->value, 0, "const expr");
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
    // do nothing more than allocate space in current AR
    // this does not harm if this is a global declaration,
    // though there are more consistent ways to do it
    frame_offset += 1;
}

void gentiny_decl_fun(FunDeclNode * node, track & track) {
    /*
     * We now have
     * - parameters saved in fp + initFO
     * - return address in ac (not saved in fp + retFO)
     * - ofp in fp + ofpFO
     */

    if (TraceCode) {
        sprintf(buffer, "-> Function (%s)", node->id.c_str());
        emitComment(buffer);
    }

    // record function location
    track.add_func(node->id, emitSkip(0));

    emitRM("ST", ac, retFO, fp, "save return address in fp + retFO");

    // generate code for the body
    // some setups
    track.current_scope = node->scope;
    // modify stack pointer
    frame_offset = initFO - param_offset(dynamic_cast<VarDeclNode *>(node->children[0]));

    emitComment("Begin function body");
    // actually generate the code
    Node * body = node->children[1];
    gentiny_code(body, track);
    emitComment("End function body");


    emitRM("LD", pc, retFO, fp, "return to caller");
}
