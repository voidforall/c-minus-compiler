
#include "util.h"
#include "parser.tab.h"
#include <iostream>
#include <string>
#include <sstream>

extern FILE * listing;

Node * find_tail(Node * node) {
    if (node != nullptr) {
        while (node->next != nullptr) {
            node = node->next;
        }
    }

    return node;
}
string print_token(int token, const std::string & text)
{
    ostringstream os;
    switch (token)
    {
        case IF: return "if";
        case ELSE: return "else";
        case RETURN: return "return";
        case WHILE: return "while";
        case INT: return "int";
        case VOID: return "void";
        case '=': case ';': case ',': case '(': case ')': case '[': case ']':
        case '{': case '}': case '+': case '-': case '*': case '/': case '>':
        case '<': return std::string(1, token).c_str();
        case NUM:
            os << "NUM: val = " << text;
            return os.str();
        case ID:
            os << "ID: name = " << text;
            return os.str();
        case ENDFILE: return "EOF";
        default: /* should never happen */
            return "UNKNOWN";
    }
}

void print_tree(Node * tree, int level) {
    string indent = string(level * 2, ' ');
    for (Node * node = tree; node != nullptr; node = node->next) {
//        cout << indent << node->str() << endl;
        string line = indent + node->str() + "\n";
        fprintf(listing, "%s", line.c_str());
        for (const auto & x: node->children) {
            print_tree(x, level + 1);
        }
    }
}

string print_type(TypeKind type) {
    switch (type) {
        case Int: return "int";
        case Void: return "void";
        default: return "error";
    }
}
string print_op(OpKind op) {
    switch (op) {
        case Eq: return "==";
        case Ne: return "!=";
        case Ge: return ">=";
        case Le: return "<=";
        case Gt: return ">";
        case Lt: return "<";
        case Plus: return "+";
        case Minus: return "-";
        case Times: return "*";
        case Divide: return "/";
        default: return "error";
    }
}
