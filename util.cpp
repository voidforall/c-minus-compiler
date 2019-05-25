#include "util.h"
#include "parser.tab.h"
#include <iostream>
#include <string>
#include <sstream>

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

