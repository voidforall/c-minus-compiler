//
// Created by ZBoom on 2019-06-01.
//

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

//=======
//#include "symtab.h"
//#include "gentiny.h"
//#include "code.h"
//
//#define ofpFO 0
//#define retFO -1
//#define initFO -2
//
//static int tmpOffset = 0; // offset relative to mp(temporary)
//>>>>>>> b3659ac3c55f26ac5cbc3733a7fd10b9cb2cefc1

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

/* gentiny is the interface to be used*/
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
    if (node->children[0] != nullptr) {
        gentiny_expr(dynamic_cast<ExprNode *>(node->children[0]), track);
    }
}

void gentiny_stmt_if(IfStmtNode * node, track & track) {
    if(TraceCode)
        emitComment("--> If");
    Node * cond = node->children[0];
    gentiny_expr((ExprNode*)cond, track);

    int loc1 = emitSkip(1);
    Node * stmt = node->children[1];
    gentiny_stmt((StmtNode*)stmt, track);

    if(node->children.size() == 3) {
        int loc2 = emitSkip(1);
        int loc3 = emitSkip(0);
        stmt = node->children[2];
        gentiny_stmt((StmtNode*)stmt, track);

        int current_loc = emitSkip(0);
        emitBackup(loc1);
        emitRM_Abs("JEQ", ac, loc3, "If false, jump to else part");
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
    if(TraceCode)
        emitComment("<-- If");
}

void gentiny_stmt_iter(IterStmtNode * node, track & track) {
    if(TraceCode)
        emitComment("--> While");
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
    if(TraceCode)
        emitComment("<-- While");
}

void gentiny_stmt_return(ReturnStmtNode * node, track & track) {
    if(TraceCode)
        emitComment("--> Return");
    Node * expr = node->children[0];
    gentiny_expr((ExprNode*)expr, track);
    if(TraceCode)
        emitComment("<-- Return");
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

void gentiny_expr_assign(AssignExprNode * node, track & track) {
    if(TraceCode)
        emitComment("--> Assign");
    IdExprNode *id = dynamic_cast<IdExprNode*>(node->children[0]);
    ExprNode *expr = dynamic_cast<ExprNode*>(node->children[1]);

    // lhs - address, rhs - value
    gentiny_expr(id, track, true);
    emitRM("ST", ac, --frame_offset, fp, "assign: push id(addr) to fp");

    gentiny_expr(expr, track, false);
    emitRM("LD", ac1, frame_offset++, fp, "assign: load id(addr) to ac1");

    // assignment in tiny(ac: expr, ac1: id)
    emitRM("ST", ac, 0, ac1, "assign: assign expr(ac)->id(ac1)");

    if(TraceCode)
        emitComment("<-- Assign");
    return ;
}

void gentiny_expr_call(CallExprNode * node, track & track) {
    if (TraceCode) {
        sprintf(buffer, "--> Calling (%s)", node->id.c_str());
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
        sprintf(buffer, "store parameter %d", param_offset);
        emitRM("ST", ac, frame_offset + initFO - param_offset, fp, buffer);
        param_offset += 1;
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
    if (TraceCode) {
        sprintf(buffer, "<-- Calling (%s)", node->id.c_str());
        emitComment(buffer);
    }
}

void gentiny_expr_op(OpExprNode * node, track & track) {
    ExprNode *op1, *op2;
    op1 = dynamic_cast<ExprNode*>(node->children[0]);
    op2 = dynamic_cast<ExprNode*>(node->children[1]);
    if(TraceCode)
        emitComment("--> Op");

    // push result value op1 to mp stack: ac->temp[mp--]
    gentiny_expr(op1, track, false);
    emitRM("ST", ac, --frame_offset, fp, "op: push operand1 to mp");

    gentiny_expr(op2, track, false);
    emitRM("LD", ac1, frame_offset++, fp, "op: load operand1 from mp");

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

void gentiny_expr_const(ConstExprNode * node, track & track) {
    if(TraceCode)
        emitComment("--> Const");

    // load const-value into register ac
    int constVal = node->value;
    emitRM("LDC", ac, constVal, 0, "Const: load val to ac");

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
    emitRO("ADD", ac, fp, ac, "ExprId: fp + offset = base address");


    BucketList list = st_lookup_list(s, node->id);
    VarDeclNode * var_node = nullptr;
    for (const auto & rec : list) {
        if (rec.id == node->id) {
            var_node = dynamic_cast<VarDeclNode *>(rec.node);
        }
    }
    // this is for the case in which x is a array parameter
    if (var_node->is_param) {
        // load absolute address
        emitRM("LD", ac, 0, ac, "load absolute address");
    }
    // may need to execute the indexExpr if it's an array
    if(node->has_index){
//         if(mem_loc >= 0 && mem_loc < param_offset())

        // a local array variable: ac-base address
        Node *index = node->children[0];
        emitRM("ST", ac, --frame_offset, fp, "ExprId: push base address to mp");
        gentiny_code(index, track);

        emitRM("LD", ac1, frame_offset++, fp, "ExprId: load base address to ac1");
        emitRO("SUB", ac, ac1, ac, "ExprId: base address - index = index address");
    }

    // isAddress - lhs like a[11], need the address of a[11]
    // the weird case is for cases like x[10], output(x)
    if(isAddress or (var_node->is_array and not node->has_index)){
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

    // do nothing more than allocate space in current AR
    // this does not harm if this is a global declaration,
    // though there are more consistent ways to do it
    if (node->is_array) {
        frame_offset -= node->num;
    }
    else
        frame_offset -= 1;


    if(TraceCode)
        emitComment("<-- DeclVar");
    return ;
}

void gentiny_decl_fun(FunDeclNode * node, track & track) {
    /*
     * We now have
     * - parameters saved in fp + initFO
     * - return address in ac (not saved in fp + retFO)
     * - ofp in fp + ofpFO
     */

    if (TraceCode) {
        sprintf(buffer, "--> Function (%s)", node->id.c_str());
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

    if (TraceCode)
        emitComment("-> Begin function body");
    // actually generate the code
    Node * body = node->children[1];
    gentiny_code(body, track);
    if (TraceCode)
        emitComment("<- End function body");


    emitRM("LD", pc, retFO, fp, "return to caller");

    if (TraceCode) {
        sprintf(buffer, "<-- Function (%s)", node->id.c_str());
        emitComment(buffer);
    }
}
