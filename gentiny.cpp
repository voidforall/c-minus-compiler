//
// Created by ZBoom on 2019-06-01.
//

#include "gentiny.h"
#include "symtab.h"
#include "gentiny.h"
#include "code.h"

#define ofpFO 0
#define retFO -1
#define initFO -2

static int tmpOffset = 0; // offset relative to mp(temporary)

static int param_offset(VarDeclNode * param_list) {
    int offset = 0;
    for (Node * node = param_list; node != nullptr; node = node->next) {
        offset += 1;
    }

    return offset;
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
            index = i;
            break;
        }
    }
    return index;
}

/* gentiny is the interface to be used*/
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
            gentiny_expr((ExprNode*)node, track, false);
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

void gentiny_expr(ExprNode * node, track & track, bool isAddress) {
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
            gentiny_expr_id((IdExprNode*)node, track, isAddress);
            break;
    }
}

// done. 问题不大
void gentiny_expr_assign(AssignExprNode * node, track & track) {
    if(TraceCode)
        emitComment("--> Assign");
    IdExprNode *id = dynamic_cast<IdExprNode*>(node->children[0]);
    ExprNode *expr = dynamic_cast<ExprNode*>(node->children[1]);

    // lhs - address, rhs - value
    gentiny_expr(id, track, true);
    emitRM("ST", ac, tmpOffset--, mp, "assign: push id(addr) to mp");

    gentiny_expr(expr, track, false);
    emitRM("LD", ac1, ++tmpOffset, mp, "assign: load id(addr) to ac1");

    // assignment in tiny(ac: expr, ac1: id)
    emitRM("ST", ac, 0, ac1, "assign: assign expr(ac)->id(ac1)");

    if(TraceCode)
        emitComment("<-- Assign");
    return ;
}

void gentiny_expr_call(CallExprNode * node, track & track) {
    string id = node->id;
    int loc = track.find_func(id);
    Node * params = node->children[0];

    for( ; params != nullptr; params = params->next) {
        gentiny_expr((ExprNode*)params, track);

    }
}
// done. tiny-like 问题不大
void gentiny_expr_op(OpExprNode * node, track & track) {
    ExprNode *op1, *op2;
    op1 = dynamic_cast<ExprNode*>(node->children[0]);
    op2 = dynamic_cast<ExprNode*>(node->children[1]);
    if(TraceCode)
        emitComment("--> Op");

    // push result value op1 to mp stack: ac->temp[mp--]
    gentiny_expr(op1, track, false);
    emitRM("ST", ac, tmpOffset--, mp, "op: push operand1 to mp");

    gentiny_expr(op2, track, false);
    emitRM("LD", ac1, ++tmpOffset, mp, "op: load operand1 from mp");

    // ac: op2 ac1: op1 -> save in ac
    switch(node->op){
        case Plus:{
            emitRO("ADD", ac, ac1, ac, "op: Plus");
            break;
        }
        case Minus:{
            emitRO("SUB", ac, ac1, ac, "op: Minus");
            break;
        }
        case Times:{
            emitRO("MUL", ac, ac1, ac, "op: Times");
            break;
        }
        case Divide:{
            emitRO("DIV", ac, ac1, ac, "op: Divide");
            break;
        }
        case Ge:{
            emitRO("SUB", ac, ac1, ac, "op: >=");
            emitRM("JGE", ac, 2, pc, "if >=, pc = pc + 2");
            emitRM("LDC", ac, 0, ac, "if false, ac = 0");
            emitRM("LDA", pc, 1, pc, "if false, skip next");
            emitRM("LDC", ac, 1, ac, "if true, ac = 1");
            break;
        }
        case Le:{
            emitRO("SUB", ac, ac1, ac, "op: <=");
            emitRM("JLE", ac, 2, pc, "if <=, pc = pc + 2");
            emitRM("LDC", ac, 0, ac, "if false, ac = 0");
            emitRM("LDA", pc, 1, pc, "if false, skip next");
            emitRM("LDC", ac, 1, ac, "if true, ac = 1");
            break;
        }
        case Gt:{
            emitRO("SUB", ac, ac1, ac, "op: >");
            emitRM("JGT", ac, 2, pc, "if >, pc = pc + 2");
            emitRM("LDC", ac, 0, ac, "if false, ac = 0");
            emitRM("LDA", pc, 1, pc, "if false, skip next");
            emitRM("LDC", ac, 1, ac, "if true, ac = 1");
            break;
        }
        case Lt:{
            emitRO("SUB", ac, ac1, ac, "op: <");
            emitRM("JLT", ac, 2, pc, "if <, pc = pc + 2");
            emitRM("LDC", ac, 0, ac, "if false, ac = 0");
            emitRM("LDA", pc, 1, pc, "if false, skip next");
            emitRM("LDC", ac, 1, ac, "if true, ac = 1");
            break;
        }
        case Eq:{
            emitRO("SUB", ac, ac1, ac, "op: ==");
            emitRM("JEQ", ac, 2, pc, "if ==, pc = pc + 2");
            emitRM("LDC", ac, 0, ac, "if false, ac = 0");
            emitRM("LDA", pc, 1, pc, "if false, skip next");
            emitRM("LDC", ac, 1, ac, "if true, ac = 1");
            break;
        }
        case Ne:{
            emitRO("SUB", ac, ac1, ac, "op: !=");
            emitRM("JNE", ac, 2, pc, "if !=, pc = pc + 2");
            emitRM("LDC", ac, 0, ac, "if false, ac = 0");
            emitRM("LDA", pc, 1, pc, "if false, skip next");
            emitRM("LDC", ac, 1, ac, "if true, ac = 1");
            break;
        }
        default:
            emitComment("[gentiny.op.error]: Invalid operator type.");
            break;
    }
    if(TraceCode)
        emitComment("<-- Op");
    return;
}

// done. tiny-like 问题不大
void gentiny_expr_const(ConstExprNode * node, track & track) {
    if(TraceCode)
        emitComment("--> Const");

    // load const-value into register ac
    int constVal = node->value;
    emitRM("LDC", ac, constVal, ac, "Const: load val to ac");

    if(TraceCode)
        emitComment("<-- Const");
    return ;
}

/* isAddress decides to calculate address or value(for array-type id) */
void gentiny_expr_id(IdExprNode * node, track & track, bool isAddress) {
    if(TraceCode)
        emitComment("--> ExprId");

    Scope s = track.current_scope;
    int mem_loc = st_lookup(s, node->id);
    int idOffset = initFO - mem_loc; // offset in the frame

    emitRM("LDC", ac, idOffset, 0, "ExprId: load id offset to ac");
    emitRM("ADD", ac, fp, ac, "ExprId: fp + offset = base address");

    // may need to execute the indexExpr if it's an array
    if(node->has_index == true){
        // if(mem_loc >= 0 && mem_loc < paramNums) 数组名参数-绝对地址

        // a local array variable: ac-base address
        Node *index = node->children[0];
        emitRM("ST", ac, tmpOffset--, mp, "ExprId: push base address to mp");
        gentiny_code(index, track, false);

        emitRM("LD", ac1, ++tmpOffset, mp, "ExprId: load base address to ac1");
        emitRM("SUB", ac, ac1, ac, "ExprId: base address - index = index address");
    }

    // isAddress - lhs like a[11], need the address of a[11]
    if(isAddress == true){
        emitRM("LDA", ac, 0, ac, "ExprId: load id address");
    }else{
        emitRM("LD", ac, 0, ac, "ExprId: load id value");
    }

    if(TraceCode)
        emitComment("<-- ExprId");
    return ;
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
    if(TraceCode)
        emitComment("--> DeclVar");






    if(TraceCode)
        emitComment("<-- DeclVar");
    return ;
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