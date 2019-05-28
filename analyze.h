#pragma once
/* analyze.h only provides two interfaces as the semantic analysis:
 * buildTable to create the symbol tables of given AST;
 * typeCheck to finish type checking using techniques in attribute calculation
 */ 
#ifndef _ANALYZE_H_
#define _ANALYZE_H_

#include "globals.h"
#include "symtab.h"

/* Function buildSymtab constructs the symbol
* table by preorder traversal of the syntax tree
*/
void buildTable(Node *syntaxTree);

/* Procedure typeCheck performs type checking
* by a postorder syntax tree traversal
*/
void typeCheck(Node *syntaxTree); // calculate type and assign to node + typecheck record to listing file

#endif