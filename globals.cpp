//
// Created by lin on 25/05/2019.
//
#include "globals.h"
#include "util.h"

string AssignExprNode::str() {
    return "Assign";
}

string Node::str() {
    return "Node";
}

string VarDeclNode::str() {
    char str[BUFSIZE];
    sprintf(str, "Decl: %s %s", print_type(kind).c_str(), id.c_str());
    return string(str);
}

string FunDeclNode::str() {
    char str[BUFSIZE];
//    return "Func";
    sprintf(str, "Func: %s %s", print_type(kind).c_str(), id.c_str());
    return string(str);
}

string IfStmtNode::str() {
    return "If";
}

string IterStmtNode::str() {
    return "While";
}

string ReturnStmtNode::str() {
    return "Return";
}

string CompoundStmtNode::str() {
    return "Block";
}

string ExprStmtNode::str() {
    return "Expr";
}

string CallExprNode::str() {
    char str[BUFSIZE];
    sprintf(str, "Call: %s", id.c_str());
    return string(str);
}

string OpExprNode::str() {
    char str[BUFSIZE];
    sprintf(str, "Op: %s", print_op(op).c_str());
    return string(str);
}

string ConstExprNode::str() {
    char str[BUFSIZE];
    sprintf(str, "Const: %d", value);
    return string(str);
}

string IdExprNode::str() {
    char str[BUFSIZE];
    sprintf(str, "Id: %s", id.c_str());
    return string(str);
}
